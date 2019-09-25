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
#include "sessionmodel.h"
#include <QGraphicsSceneMouseEvent>

using namespace ModelView;

namespace {
enum class MouseReleaseAction {NO_CHANGE, CHANGE_OWNER, CHANGE_POSITION, RELEASE};
int adjustInsertionRow(const ILayerView* child, const ILayerView* new_parent, int insertion_row);
} // namespace

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

auto ILayerView::determineAction(const MultiLayerView *new_parent, int row)
{
    // Simple move of single layer on the scene
    if (!new_parent && !parentItem())
        return MouseReleaseAction::CHANGE_POSITION;

    // Layer was moved from MultiLayer it belongs to, to an empty place of
    // the scene: changing ownership.
    if (parentItem() && !new_parent)
        return MouseReleaseAction::RELEASE;

    // Layer was moved either from one MultiLayer to another, or is moved inside
    // one multilayer: changing ownership or row within same ownership.
    if (new_parent && row >= 0)
        return MouseReleaseAction::CHANGE_OWNER;

    return MouseReleaseAction::NO_CHANGE;
}

//! Detects possible MultiLayerView's to drop given ILayerView and propagate
//! request to SessionModel.
void ILayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DesignerScene* designerScene = dynamic_cast<DesignerScene*>(scene());
    Q_ASSERT(designerScene);
    designerScene->setLayerInterfaceLine(); // removing drop area hint from the scene

    const auto [requested_parent, requested_row] = DesignerSceneUtils::nearestMultilayer(*this);
    const MouseReleaseAction action_type = determineAction(requested_parent, requested_row);

    if (action_type == MouseReleaseAction::NO_CHANGE) {
        setPos(m_drag_start_position);
    } else if (action_type == MouseReleaseAction::RELEASE) {
        const QPointF newPos = mapToScene(event->pos()) - event->pos();
        getItem()->setProperty(LocatedItem::P_X_POS, newPos.x());
        getItem()->setProperty(LocatedItem::P_Y_POS, newPos.y());

        designerScene->setDelayedExecution([item = getItem()](ModelView::SessionModel& model) {
            model.moveItem(item, model.rootItem(), {}, -1);
        });
    } else if (action_type == MouseReleaseAction::CHANGE_OWNER) {
        const int insertion_row = adjustInsertionRow(this, requested_parent, requested_row);
        designerScene->setDelayedExecution([item = getItem(),
                                            new_parent = requested_parent->getItem(),
                                            insertion_row](ModelView::SessionModel& model) {
            model.moveItem(item, new_parent, MultiLayerItem::T_LAYERS, insertion_row);
        });
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

namespace {
int adjustInsertionRow(const ILayerView* child, const ILayerView* new_parent, int insertion_row)
{
    const SessionItem* child_item = child->getItem();
    if (new_parent == child->parentItem()
        && insertion_row > child_item->parent()->tagRowOfItem(child_item).second)
        return insertion_row - 1;

    return insertion_row;
}
}
