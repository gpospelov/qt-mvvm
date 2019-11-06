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
#include "DesignerSceneUtils.h"
#include "LayerItems.h"
#include "MultiLayerView.h"
#include <mvvm/model/sessionmodel.h>
#include <QGraphicsSceneMouseEvent>

using namespace ModelView;

namespace {
enum class MouseReleaseAction {NO_CHANGE, CHANGE_OWNER, CHANGE_POSITION, RELEASE};
int itemRow(const SessionItem* item);
} // namespace

ILayerView::ILayerView(QGraphicsItem* parent, int view_type)
    : ConnectableView(parent, view_type)
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

        const auto [multilayer, row] = DesignerSceneUtils::nearestMultilayer(*this);
        if (multilayer) {
            DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
            designerScene->setLayerInterfaceLine(
                DesignerSceneUtils::getInterfaceToScene(*multilayer, row));
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

auto ILayerView::determineAction(const MultiLayerView* new_parent, int row) const
{
    // Simple move of a single ILayerView instance on the scene
    if (!new_parent && !parentItem())
        return MouseReleaseAction::CHANGE_POSITION;

    // ILayerView instance was moved from MultiLayer it belongs to, to an empty place of
    // the scene: changing ownership.
    if (parentItem() && !new_parent)
        return MouseReleaseAction::RELEASE;

    // ILayerView instance was moved, but both parent and the row remained the same.
    // All the changes will be cancelled.
    if (parentItem() == new_parent && insertionRow(new_parent, row) == itemRow(getItem()))
        return MouseReleaseAction::NO_CHANGE;

    // ILayerView instance was moved either from one multiLayer to another, or is moved inside
    // one multilayer: changing ownership or row within same ownership.
    if (new_parent && row >= 0)
        return MouseReleaseAction::CHANGE_OWNER;

    return MouseReleaseAction::NO_CHANGE;
}

//! Detects possible MultiLayerView's to drop given ILayerView and propagate
//! request to SessionModel.
void ILayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    const auto [requested_parent, requested_row] = DesignerSceneUtils::nearestMultilayer(*this);
    const MouseReleaseAction action_type = determineAction(requested_parent, requested_row);

    switch (action_type) {
    case MouseReleaseAction::NO_CHANGE:
        onNoChange();
        break;
    case MouseReleaseAction::RELEASE:
        onRelease(event->pos());
        break;
    case MouseReleaseAction::CHANGE_OWNER:
        onChangeOwner(requested_parent, requested_row);
        break;
    default:
        break;
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

void ILayerView::onNoChange()
{
    setPos(m_drag_start_position);
}

void ILayerView::onRelease(const QPointF& pos)
{
    const QPointF newPos = mapToScene(pos) - pos;
    getItem()->setProperty(LocatedItem::P_X_POS, newPos.x());
    getItem()->setProperty(LocatedItem::P_Y_POS, newPos.y());

    dynamic_cast<DesignerScene*>(scene())->sendModelCommand(
        [item = getItem()](ModelView::SessionModel& model) {
            model.moveItem(item, model.rootItem(), {}, -1);
        });
}

void ILayerView::onChangeOwner(const ILayerView* requested_parent, int requested_row)
{
    const int insertion_row = insertionRow(requested_parent, requested_row);
    dynamic_cast<DesignerScene*>(scene())->sendModelCommand([item = getItem(),
                                        new_parent = requested_parent->getItem(),
                                        insertion_row](ModelView::SessionModel& model) {
        model.moveItem(item, new_parent, MultiLayerItem::T_LAYERS, insertion_row);
    });
}

int ILayerView::insertionRow(const ILayerView* new_parent, int insertion_row) const
{
    const SessionItem* child_item = getItem();
    if (new_parent == parentItem()
        && insertion_row > child_item->parent()->tagRowOfItem(child_item).row)
        return insertion_row - 1;

    return insertion_row;
}

namespace {
int itemRow(const SessionItem* item)
{
    return item->parent()->tagRowOfItem(item).row;
}
}
