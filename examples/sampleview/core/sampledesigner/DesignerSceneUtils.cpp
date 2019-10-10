// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "DesignerSceneUtils.h"
#include "MultiLayerView.h"
#include <QGraphicsScene>
#include <limits>

namespace {
QList<QGraphicsItem*> intersectingItems(const ILayerView& view)
{
    const QGraphicsScene* scene = view.scene();
    if (!scene)
        return {};
    const QRectF intersect_bound = view.sceneBoundingRect();

    QList<QGraphicsItem*> all_items = scene->items(intersect_bound, Qt::IntersectsItemBoundingRect);
    QList<QGraphicsItem*> in_items = scene->items(intersect_bound, Qt::ContainsItemBoundingRect);
    QList<QGraphicsItem*> result;

    std::copy_if(
        all_items.begin(), all_items.end(), std::back_inserter(result),
        [&in_items, view_item = dynamic_cast<const QGraphicsItem*>(&view)](QGraphicsItem* item) {
            return !in_items.contains(item) && item != view_item;
        });

    return result;
}
}

QLineF DesignerSceneUtils::getInterfaceToScene(const MultiLayerView& sample, int row)
{
    QLineF line = sample.getInterfaceLine(row);
    if(line.length() != 0) {
        QPointF p1(sample.mapToScene(line.p1()));
        QPointF p2(sample.mapToScene(line.p2()));
        const int prolongation = 20.0;
        return QLineF(p1.x() -prolongation, p1.y(), p2.x()+prolongation, p2.y());
    }

    return QLineF();
}

std::tuple<MultiLayerView*, int>
DesignerSceneUtils::nearestMultilayer(const ILayerView& view)
{
    const QList<QGraphicsItem*> items = intersectingItems(view);
    const QPointF scene_pos = view.scenePos();

    std::tuple<MultiLayerView*, int> result{nullptr, -1};
    qreal distance = std::numeric_limits<qreal>::max();
    for (auto item : items) {
        MultiLayerView* multilayer = dynamic_cast<MultiLayerView*>(item);
        if (!multilayer)
            continue;

        // calculate row number to drop ILayerView and distance to the nearest droping area
        int row = multilayer->getDropArea(multilayer->mapFromScene(scene_pos));
        const QRectF droparea = multilayer->mapRectToScene(multilayer->getDropAreaRectangle(row));
        const qreal current_distance = std::abs(droparea.center().y() - scene_pos.y());
        if (distance > current_distance) {
            result = {multilayer, row};
            distance = current_distance;
        }
    }
    return result;
}
