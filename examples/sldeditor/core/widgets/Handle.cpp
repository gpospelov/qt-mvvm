// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "Handle.h"
#include "HandleItem.h"
#include "AxisObject.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsSceneMouseEvent>

#include <cmath>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/utils/numericutils.h>

#include <iostream>


Handle::Handle(HandleItem* item) : 
    handle_item(item), 
    color(item->property(HandleItem::P_COLOR).value<QColor>())
{
    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == HandleItem::P_XPOS){
            update();
            emit moved();
        }
        if (property_name == HandleItem::P_YPOS){
            update();
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

void Handle::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    AxisObject* axis = getAxes();
    if (!axis) return;

    painter->setBrush(color);
    painter->drawEllipse(
        QPointF(
            axis->fromRealToSceneX(handle_item->property(HandleItem::P_XPOS).toDouble()),
            axis->fromRealToSceneY(handle_item->property(HandleItem::P_YPOS).toDouble())
        ),
        handle_item->property(HandleItem::P_RADIUS).toDouble()/2.,
        handle_item->property(HandleItem::P_RADIUS).toDouble()/2.
    );
}

QPainterPath Handle::shape() const
{
    QPainterPath path;

    AxisObject* axis = getAxes();
    if (!axis) return path;

    path.addRect(
        axis->fromRealToSceneX(handle_item->property(HandleItem::P_XPOS).toDouble() 
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2),
        axis->fromRealToSceneY(handle_item->property(HandleItem::P_YPOS).toDouble()
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2),
        handle_item->property(HandleItem::P_RADIUS).toDouble(),
        handle_item->property(HandleItem::P_RADIUS).toDouble()
    );
    return path;
}

QRectF Handle::boundingRect() const
{
    double epsilon = 10;

    AxisObject* axis = getAxes();
    if (!axis) return QRectF(0,0,1,1);

    return QRectF(
        axis->fromRealToSceneX(handle_item->property(HandleItem::P_XPOS).toDouble() 
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2)-epsilon,
        axis->fromRealToSceneY(handle_item->property(HandleItem::P_YPOS).toDouble()
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2)-epsilon,
        handle_item->property(HandleItem::P_RADIUS).toDouble()+2*epsilon,
        handle_item->property(HandleItem::P_RADIUS).toDouble()+2*epsilon
    );
}

void Handle::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    AxisObject* axis = getAxes();
    if (!axis) return ;

    handle_item->setProperty(HandleItem::P_XPOS, axis->fromSceneToRealX(double(x()+ event->pos().x())));
}

