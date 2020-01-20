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
#include <cmath>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/utils/numericutils.h>

#include <iostream>


Handle::Handle(HandleItem* item) : 
    handle_item(item), 
    color(item->property(HandleItem::P_COLOR).value<QColor>())
{
    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == HandleItem::P_XPOS)
            setX(handle_item->property(HandleItem::P_XPOS).toDouble());
        if (property_name == HandleItem::P_YPOS)
            setY(handle_item->property(HandleItem::P_YPOS).toDouble());
        if (property_name == HandleItem::P_COLOR)
            color = handle_item->property(HandleItem::P_COLOR).value<QColor>();
    };
    handle_item->mapper()->setOnPropertyChange(on_property_change, this);

    setPos(item->property(HandleItem::P_XPOS).toDouble(),
           item->property(HandleItem::P_YPOS).toDouble());

    setFlag(QGraphicsItem::ItemIsMovable);

}

void Handle::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setBrush(color);
    painter->drawEllipse(-10, -10, 20, 20);
}

QPainterPath Handle::shape() const
{
    QPainterPath path;
    path.addRect(-10, -10, 20, 20);
    return path;
}

QRectF Handle::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void Handle::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    _dragged = true;
    handle_item->setProperty(HandleItem::P_XPOS, double(x()));
    handle_item->setProperty(HandleItem::P_YPOS, double(y()));
    QGraphicsItem::mouseMoveEvent(event);
}
