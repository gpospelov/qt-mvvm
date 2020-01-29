// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "HandleView.h"
#include "AxisObject.h"
#include "HandleItem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include <cmath>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/utils/numericutils.h>

#include <iostream>

//! The constructor
HandleView::HandleView(HandleItem* item)
    : handle_item(item), color(item->property(HandleItem::P_COLOR).value<QColor>())
{
    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == HandleItem::P_XPOS) {
            AxisObject* axis = getAxes();
            setX(axis->fromRealToSceneX(handle_item->property(HandleItem::P_XPOS).toDouble()));
            emit moved();
        }
        if (property_name == HandleItem::P_YPOS) {
            AxisObject* axis = getAxes();
            setY(axis->fromRealToSceneY(handle_item->property(HandleItem::P_YPOS).toDouble()));
            emit moved();
        }
        if (property_name == HandleItem::P_COLOR)
            color = handle_item->property(HandleItem::P_COLOR).value<QColor>();
        if (property_name == HandleItem::P_RADIUS)
            update();
    };

    handle_item->mapper()->setOnPropertyChange(on_property_change, this);
    setZValue(20);
}

//! The overriden paint method
void HandleView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    AxisObject* axis = getAxes();
    if (!axis)
        return;

    painter->setBrush(color);
    painter->drawEllipse(QPointF(0, 0), handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.,
                         handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.);
}

//! The shape
QPainterPath HandleView::shape() const
{
    QPainterPath path;

    AxisObject* axis = getAxes();
    if (!axis)
        return path;

    path.addRect(getSceneRect());
    return path;
}

//! The bounding rectangle of the handle
QRectF HandleView::boundingRect() const
{
    double epsilon = 10;

    AxisObject* axis = getAxes();
    if (!axis)
        return QRectF(0, 0, 1, 1);

    return getSceneRect();
}

//! Get the scene rectangle
QRectF HandleView::getSceneRect() const
{
    AxisObject* axis = getAxes();
    if (!axis)
        return QRectF(0, 0, 1, 1);

    return QRectF(
        QPointF(
            axis->fromRealToSceneX(-handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.),
            axis->fromRealToSceneY(+handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.)),
        QPointF(
            axis->fromRealToSceneX(handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.),
            axis->fromRealToSceneY(-handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.)));
}

//! On move update the model
void HandleView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    AxisObject* axis = getAxes();
    if (!axis)
        return;

    handle_item->setProperty(HandleItem::P_XPOS,
                             axis->fromSceneToRealX(double(x() + event->pos().x())));
}

//! Return a pointer to the handle item
HandleItem* HandleView::handleItem() const
{
    return handle_item;
}
