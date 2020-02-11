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
    QGraphicsItem::mouseMoveEvent(event);
    controller->update_item_from_view();
}
