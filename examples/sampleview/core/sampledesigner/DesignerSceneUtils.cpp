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
#include "SampleViewFactory.h"
#include "modelutils.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <limits>

using namespace ModelView;

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

//! Returns all ancestors of the argument
QSet<SessionItem*> ancestors(const SessionItem* item)
{
    QSet<SessionItem*> result;
    SessionItem* parent = item->parent();
    while (parent) {
        result.insert(parent);
        parent = parent->parent();
    }
    return result;
}

template<class InputIterator>
QList<SessionItem*> visibleItems(const InputIterator& begin, const InputIterator& end)
{
    QList<ModelView::SessionItem*> result;
    std::copy_if(begin, end, std::back_inserter(result), [](const auto& item) {
        return SampleViewFactory::isValidType(item->modelType());
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

QSet<SessionItem*> DesignerSceneUtils::headItems(const QSet<SessionItem*>& items)
{
    QSet<SessionItem*> result;
    for (SessionItem* item: items)
        if (!items.intersects(ancestors(item)))
            result.insert(item);

    return result;
}

std::map<SessionItem*, SessionItem*> DesignerSceneUtils::makeLookupTable(SessionItem* origin,
                                                                         SessionItem* copy)
{
    if (!origin || !copy)
        throw std::runtime_error(
            "Error in DesignerSceneUtils::makeLookupTable: one of the input arguments is null.");

    std::vector<SessionItem*> origin_tree;
    Utils::iterate(origin, [&origin_tree](SessionItem* item) { origin_tree.push_back(item); });

    std::vector<SessionItem*> copy_tree;
    Utils::iterate(copy, [&copy_tree](SessionItem* item) { copy_tree.push_back(item); });

    if (origin_tree.size() != copy_tree.size())
        throw std::runtime_error(
            "Error in DesignerSceneUtils::makeLookupTable: origin and copy tree sizes differ.");

    std::map<SessionItem*, SessionItem*> result;
    std::transform(origin_tree.begin(), origin_tree.end(), copy_tree.begin(),
                   std::inserter(result, result.end()), [](auto lhs, auto rhs) {
                       return std::pair{lhs, rhs};
                   });

    return result;
}

QSet<QGraphicsItem*> DesignerSceneUtils::appendChildren(QList<QGraphicsItem*> views)
{
    QSet<QGraphicsItem*> result;
    while (!views.empty()) {
        QGraphicsItem* view = views.takeFirst();
        result.insert(view);
        views.append(view->childItems());
    }
    return result;
}

QList<SessionItem*> DesignerSceneUtils::visibleItems(const std::vector<SessionItem*>& items)
{
    return ::visibleItems(items.begin(), items.end());
}

QList<SessionItem*> DesignerSceneUtils::visibleItems(const QSet<SessionItem*>& items)
{
    return ::visibleItems(items.begin(), items.end());
}
