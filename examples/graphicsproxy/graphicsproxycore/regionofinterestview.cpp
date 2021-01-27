// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "regionofinterestview.h"
#include "regionofinterestcontroller.h"
#include "sizehandleelement.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <stdexcept>

namespace {
const double bbox_margins = 5; // additional margins around rectangle to form bounding box
} // namespace

namespace GraphicsProxy {

RegionOfInterestView::RegionOfInterestView(RegionOfInterestItem* item,
                                           const ModelView::SceneAdapterInterface* scene_adapter)
    : m_controller(std::make_unique<RegionOfInterestController>(scene_adapter, item, this))
{
    if (!scene_adapter)
        throw std::runtime_error("Error in RegionOfInterestView: scene adapter is not initialized");

    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    create_size_handle_elements();
}

RegionOfInterestView::~RegionOfInterestView() = default;

QRectF RegionOfInterestView::boundingRect() const
{
    return m_controller->roiRectangle().marginsAdded(
        QMarginsF(bbox_margins, bbox_margins, bbox_margins, bbox_margins));
}

//! Updates view appearance from RegionOfInterestItem.
//! Triggered by QGraphicsScene::advance method on a) QGraphicsView resize b) zoom in/out
//! events in QCustomPlot.

void RegionOfInterestView::advance(int phase)
{
    if (!phase)
        return;
    update_geometry();
}

void RegionOfInterestView::setActiveHandle(SizeHandleElement* element)
{
    setFlag(QGraphicsItem::ItemIsMovable, element ? false : true);
    m_activeHandle = element;
    // saving position of opposite corner to allow resize
    if (m_activeHandle)
        m_oppositeOrigin = findOpposite(m_activeHandle)->scenePos();
}

//! Recalculates view rectangle and position of handles using properties of RegionOfInterestItem.

void RegionOfInterestView::update_geometry()
{
    prepareGeometryChange();
    m_controller->updateViewFromItem();
    for (auto handle : m_handles)
        handle->updateHandleElementPosition(m_controller->roiRectangle());
}

void RegionOfInterestView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // drawing rectangular frame made of two colors to look good on both black and white
    painter->setPen(QPen(QColor(34, 67, 255)));
    painter->drawRect(m_controller->roiRectangle());
    QRectF secondRect = m_controller->roiRectangle().marginsAdded(QMarginsF(1, 1, 1, 1));
    painter->setPen(QPen(QColor(255, 255, 245)));
    painter->drawRect(secondRect);
}

void RegionOfInterestView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_activeHandle) {

        auto left = std::min(event->scenePos().x(), m_oppositeOrigin.x());
        auto right = std::max(event->scenePos().x(), m_oppositeOrigin.x());
        auto bottom = std::min(event->scenePos().y(), m_oppositeOrigin.y());
        auto top = std::max(event->scenePos().y(), m_oppositeOrigin.y());

        if (m_activeHandle->isCornerHandle())
            m_controller->updateItemFromCorner(left, right, top, bottom);
        else if (m_activeHandle->isVerticalHandle())
            m_controller->updateItemFromVerticalHandle(top, bottom);
        else if (m_activeHandle->isHorizontalHandle())
            m_controller->updateItemFromHorizontalHandle(left, right);

        update_geometry();
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
        m_controller->updateItemFromView();
    }
}

//! Show/hides handles on rectangle selection/deselection.

QVariant RegionOfInterestView::itemChange(QGraphicsItem::GraphicsItemChange change,
                                          const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
        for (auto handle : m_handles)
            handle->setVisible(!this->isSelected());
    return value;
}

void RegionOfInterestView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // SizeHandleElement::mouseReleaseEvent is not triggered, so we have to do it here
    setActiveHandle(nullptr);
    QGraphicsItem::mouseReleaseEvent(event);
}

void RegionOfInterestView::create_size_handle_elements()
{
    for (auto pos_type : SizeHandleElement::possible_handle_positions())
        m_handles.push_back(SizeHandleElement::create(pos_type, this));
}

//! Finds handle element which is located on "opposite" rectangle corner with
//! respect to currently selected one.

SizeHandleElement* RegionOfInterestView::findOpposite(SizeHandleElement* element)
{
    if (!element)
        return nullptr;

    auto opposite = element->oppositeHandlePosition();
    auto it = std::find_if(m_handles.begin(), m_handles.end(),
                           [opposite](auto x) { return x->handlePosition() == opposite; });
    if (it == m_handles.end())
        throw std::runtime_error("Error in RegionOfInterestView: can't find opposite handle");
    return *it;
}

} // namespace GraphicsProxy
