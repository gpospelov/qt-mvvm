// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "regionofinterestview.h"
#include "sceneitems.h"
#include <QPainter>
#include <QDebug>
#include <mvvm/plotting/sceneadapterinterface.h>

namespace
{
const double bbox_margins = 5; // additional margins around rectangle to form bounding box
} // namespace

RegionOfInterestView::RegionOfInterestView(RegionOfInterestItem* item,
                                           const ModelView::SceneAdapterInterface* scene_adapter)
    : item(item), scene_adapter(scene_adapter)
{
    if (!scene_adapter)
        throw std::runtime_error("Error in RegionOfInterestView: scene adapter is not initialized");

    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);

    update_geometry();
}

QRectF RegionOfInterestView::boundingRect() const
{
    return rect.marginsAdded(QMarginsF(bbox_margins, bbox_margins, bbox_margins, bbox_margins));
}

void RegionOfInterestView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // drawing rectangular frame made of two colors to look good on both black and white
    painter->setPen(QPen(QColor(34, 67, 255)));
    painter->drawRect(rect);
    QRectF secondRect = rect.marginsAdded(QMarginsF(1, 1, 1, 1));
    painter->setPen(QPen(QColor(255, 255, 245)));
    painter->drawRect(secondRect);
}

//! Updates geometry from item.

void RegionOfInterestView::update_geometry()
{
    prepareGeometryChange();
    rect = QRectF(0.0, 0.0, width(), height());
    setX(scene_adapter->toSceneX(par(RegionOfInterestItem::P_XLOW)));
    setY(scene_adapter->toSceneY(par(RegionOfInterestItem::P_YUP)));
}

qreal RegionOfInterestView::width() const
{
    return right() - left();
}

qreal RegionOfInterestView::height() const
{
    return bottom() - top();
}

//! returns the x-coordinate of the rectangle's left edge

qreal RegionOfInterestView::left() const
{
    return scene_adapter->toSceneX(par(RegionOfInterestItem::P_XLOW));
}

//! returns the x-coordinate of the rectangle's right edge

qreal RegionOfInterestView::right() const
{
    return scene_adapter->toSceneX(par(RegionOfInterestItem::P_XUP));
}

//! Returns the y-coordinate of the rectangle's top edge.

qreal RegionOfInterestView::top() const
{
    return scene_adapter->toSceneY(par(RegionOfInterestItem::P_YUP));
}

//! Returns the y-coordinate of the rectangle's bottom edge.

qreal RegionOfInterestView::bottom() const
{
    return scene_adapter->toSceneY(par(RegionOfInterestItem::P_YLOW));
}

double RegionOfInterestView::par(const std::string& name) const
{
    return item->property(name).value<double>();
}
