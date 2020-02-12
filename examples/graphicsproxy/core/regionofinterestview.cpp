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
#include "sceneitems.h"
#include "sizehandleelement.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <mvvm/plotting/sceneadapterinterface.h>

namespace
{
const double bbox_margins = 5; // additional margins around rectangle to form bounding box
} // namespace

RegionOfInterestView::RegionOfInterestView(RegionOfInterestItem* item,
                                           const ModelView::SceneAdapterInterface* scene_adapter)
    : controller(std::make_unique<RegionOfInterestController>(item, scene_adapter, this))
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
    return controller->roi_rectangle().marginsAdded(
        QMarginsF(bbox_margins, bbox_margins, bbox_margins, bbox_margins));
}

void RegionOfInterestView::advance(int phase)
{
    if (!phase)
        return;
    prepareGeometryChange();
    controller->update_view_from_item();
    for (auto handle : handles)
        handle->updateHandleElementPosition(controller->roi_rectangle());
}

void RegionOfInterestView::setActiveHandle(SizeHandleElement* element)
{
    qDebug() << "element" << element;
    setFlag(QGraphicsItem::ItemIsMovable, element ? false : true);
    active_handle = element;
}

void RegionOfInterestView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // drawing rectangular frame made of two colors to look good on both black and white
    painter->setPen(QPen(QColor(34, 67, 255)));
    painter->drawRect(controller->roi_rectangle());
    QRectF secondRect = controller->roi_rectangle().marginsAdded(QMarginsF(1, 1, 1, 1));
    painter->setPen(QPen(QColor(255, 255, 245)));
    painter->drawRect(secondRect);
}

void RegionOfInterestView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

    if (active_handle) {
        auto opposite = findOpposite(active_handle)->pos();

        auto left = std::min(event->scenePos().x(), opposite.x());
        auto right = std::max(event->scenePos().x(), opposite.x());
        auto bottom = std::min(event->scenePos().y(), opposite.y());
        auto top = std::max(event->scenePos().y(), opposite.y());

        if (active_handle->isCornerHandle()) {
            controller->update_item_from_corner(left, right, top, bottom);

        } else if (active_handle->isVerticalHandle()) {
            controller->update_item_from_vertical_handle(top, bottom);

        } else if (active_handle->isHorizontalHandle()) {
            controller->update_item_from_horizontal_handle(left, right);
        }

        prepareGeometryChange();
        controller->update_view_from_item();
        for (auto handle : handles)
            handle->updateHandleElementPosition(controller->roi_rectangle());

    } else {
        QGraphicsItem::mouseMoveEvent(event);
        controller->update_item_from_view();
    }
}

//! Show/hides handles on rectangle selection/deselection.

QVariant RegionOfInterestView::itemChange(QGraphicsItem::GraphicsItemChange change,
                                          const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedChange) {
        for (auto handle : handles)
            handle->setVisible(!this->isSelected());
    }
    return value;
}

void RegionOfInterestView::create_size_handle_elements()
{
    for (auto pos_type : SizeHandleElement::possible_handle_positions())
        handles.push_back(SizeHandleElement::create(pos_type, this));
}

SizeHandleElement* RegionOfInterestView::findOpposite(SizeHandleElement* element)
{
    if (!element)
        return nullptr;

    auto opposite = element->oppositeHandlePosition();
    auto it = std::find_if(handles.begin(), handles.end(),
                           [opposite](auto x) { return x->handlePosition() == opposite; });
    if (it == handles.end())
        throw std::runtime_error("Error in RegionOfInterestView: can't find opposite handle");
    return *it;
}
