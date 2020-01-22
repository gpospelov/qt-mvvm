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
            setX(handle_item->property(HandleItem::P_XPOS).toDouble());
            emit moved();
        }
        if (property_name == HandleItem::P_YPOS){
            setY(handle_item->property(HandleItem::P_YPOS).toDouble());
            emit moved();
        }
        if (property_name == HandleItem::P_COLOR)
            color = handle_item->property(HandleItem::P_COLOR).value<QColor>();
        if (property_name == HandleItem::P_RADIUS)
            update();
    };
    handle_item->mapper()->setOnPropertyChange(on_property_change, this);

    setPos(item->property(HandleItem::P_XPOS).toDouble(),
           item->property(HandleItem::P_YPOS).toDouble());

    // setFlag(QGraphicsItem::ItemIsMovable);
    setZValue(20);

}

void Handle::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setBrush(color);
    painter->drawEllipse(
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2,
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2,
        handle_item->property(HandleItem::P_RADIUS).toDouble(),
        handle_item->property(HandleItem::P_RADIUS).toDouble()
    );
}

QPainterPath Handle::shape() const
{
    QPainterPath path;
    path.addRect(
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2,
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2,
        handle_item->property(HandleItem::P_RADIUS).toDouble(),
        handle_item->property(HandleItem::P_RADIUS).toDouble()
    );
    return path;
}

QRectF Handle::boundingRect() const
{
    double epsilon = 10;
    return QRectF(
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2 - epsilon,
        - handle_item->property(HandleItem::P_RADIUS).toDouble()/2 - epsilon,
        handle_item->property(HandleItem::P_RADIUS).toDouble() + 2*epsilon,
        handle_item->property(HandleItem::P_RADIUS).toDouble() + 2*epsilon
    );
}

void Handle::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    handle_item->setProperty(HandleItem::P_XPOS, double(x()+ event->pos().x()));
    // handle_item->setProperty(HandleItem::P_YPOS, double(y()+ event->pos().y()));
}

