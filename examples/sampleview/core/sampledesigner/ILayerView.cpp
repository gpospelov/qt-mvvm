// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "ILayerView.h"
#include "DesignerHelper.h"
#include "DesignerScene.h"
#include "LayerItems.h"
#include "MultiLayerView.h"
#include "SampleModel.h"
#include "externalproperty.h"
#include <QGraphicsSceneMouseEvent>

using namespace ModelView;

QLineF MultiLayerCandidate::getInterfaceToScene()
{
    Q_ASSERT(multilayer);
    QLineF line = multilayer->getInterfaceLine(row);
    if(line.length() != 0) {
        QPointF p1(multilayer->mapToScene(line.p1()));
        QPointF p2(multilayer->mapToScene(line.p2()));
        const int prolongation = 20.0;
        return QLineF(p1.x() -prolongation, p1.y(), p2.x()+prolongation, p2.y());
    }

    return QLineF();
}

bool MultiLayerCandidate::operator<(const MultiLayerCandidate &cmp) const
{
    return cmp.distance < distance;
}

ILayerView::ILayerView(QGraphicsItem *parent) : ConnectableView(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

ILayerView::~ILayerView() = default;

//! Detects movement of the ILayerView and sends possible drop areas to GraphicsScene
//! for visualization.
QVariant ILayerView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {

        MultiLayerCandidate multilayerCandidate = getMultiLayerCandidate();
        if (multilayerCandidate) {
            DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
            designerScene->setLayerInterfaceLine(multilayerCandidate.getInterfaceToScene());
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void ILayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_drag_start_position = pos();
    }
    QGraphicsItem::mousePressEvent(event);
}

//! Detects possible MultiLayerView's to drop given ILayerView and propagate
//! request to SessionModel.
void ILayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
    Q_ASSERT(designerScene);
    designerScene->setLayerInterfaceLine(); // removing drop area hint from the scene

    if (QLineF(m_drag_start_position, pos()).length() == 0) {
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    MultiLayerCandidate candidate = getMultiLayerCandidate();
    MultiLayerView *requested_parent = candidate.multilayer;
    int requested_row = candidate.row;

    // Simple move of single layer on the scene
    if (requested_parent == nullptr && parentItem() == nullptr) {
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved on top of MultiLayer but not in the right drop area:
    // returning layer back to starting position.
    if (requested_parent && requested_row == -1) {
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    SampleModel *model = designerScene->getSampleModel();

    // Layer was moved only slightly, to the same row of his own MultiLayer: returning back.
    if (requested_parent == parentItem()
        && requested_row == getItem()->parent()->tagRowOfItem(getItem()).second) {
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved from MultiLayer it belongs to, to an empty place of
    // the scene: changing ownership.
    if (parentItem() && !requested_parent) {
        QPointF newPos = mapToScene(event->pos()) - event->pos();
        getItem()->setItemValue(LocatedItem::P_X_POS, newPos.x());
        getItem()->setItemValue(LocatedItem::P_Y_POS, newPos.y());

        model->moveItem(getItem(), model->rootItem(), {}, -1);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved either from one MultiLayer to another, or is moved inside
    // one multilayer: changing ownership or row within same ownership.
    if (requested_parent) {
        SessionItem* new_parent = requested_parent->getItem();
        const std::string tag = MultiLayerItem::T_LAYERS;
        int insertion_row = requested_row >= new_parent->itemCount(tag) ? -1 : requested_row;
        model->moveItem(getItem(), new_parent, tag, insertion_row);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // throw only happens when not all cases were considered previously
    throw std::runtime_error("LayerView::mouseReleaseEvent() -> Loggic error.");
}

//! Finds candidate (another MultiLayer) into which we will move our ILayerView.
//!
//! To become the candidate, the bounding rectangles of MultiLayerView and given
//! ILayerView should intersects and ILayerView center should be near appropriate
//! drop area. If more than one candidate is found, they will be sorted according
//! to the distance between drop area and ILayerVIew center
MultiLayerCandidate ILayerView::getMultiLayerCandidate()
{
    QVector<MultiLayerCandidate> candidates;

    QRectF layerRect = mapRectToScene(boundingRect());
    for(auto item : scene()->items()) {
        if (item->type() == DesignerHelper::MULTILAYER && item != this
            && !childItems().contains(item)) {
            MultiLayerView *multilayer = qgraphicsitem_cast<MultiLayerView *>(item);
            if (multilayer->mapRectToScene(multilayer->boundingRect()).intersects(layerRect)) {
                MultiLayerCandidate candidate;

                // calculate row number to drop ILayerView and distance to the nearest droping area
                int row = multilayer->getDropArea(multilayer->mapFromScene(layerRect.center()));
                QRectF droparea = multilayer->mapRectToScene(multilayer->getDropAreaRectangle(row));
                int distance = std::abs(droparea.center().y() - layerRect.center().y());

                candidate.multilayer = multilayer;
                candidate.row = row;
                candidate.distance = distance;
                candidates.push_back(candidate);
            }
        }
    }
    // sorting MultiLayerView candidates to find one whose drop area is closer
    if (candidates.size()) {
        std::sort(candidates.begin(), candidates.end());
        return candidates.back();
    }
    return MultiLayerCandidate();
}
