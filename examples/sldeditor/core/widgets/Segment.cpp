// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "Segment.h"
#include "SegmentItem.h" 

#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QPainter>
#include <QStyleOption>
#include <cmath>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/utils/numericutils.h>

#include <iostream>


Segment::Segment(SegmentItem* item) : 
    segment_item(item), 
    color(item->property(SegmentItem::P_COLOR).value<QColor>()),
    _left_handle(nullptr),
    _right_handle(nullptr)
{
    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == SegmentItem::P_X_FIN)
            parentWidget()->update();
        if (property_name == SegmentItem::P_X_INI)
            parentWidget()->update();
        if (property_name == SegmentItem::P_Y_INI)
            parentWidget()->update();
        if (property_name == SegmentItem::P_Y_FIN)
            parentWidget()->update();
        if (property_name == SegmentItem::P_COLOR)
            parentWidget()->update();
    };
    segment_item->mapper()->setOnPropertyChange(on_property_change, this);

    double x_m = (
        segment_item->property(SegmentItem::P_X_FIN).toDouble()
        - segment_item->property(SegmentItem::P_X_INI).toDouble()) / 2
        + segment_item->property(SegmentItem::P_X_INI).toDouble();
    double y_m = (
        segment_item->property(SegmentItem::P_Y_FIN).toDouble()
        - segment_item->property(SegmentItem::P_Y_INI).toDouble()) / 2
        + segment_item->property(SegmentItem::P_Y_INI).toDouble();

    setPos(x_m,y_m);

    setFlag(QGraphicsItem::ItemIsMovable);

}

void Segment::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(QPen(color, 12));
    painter->drawLine(
        segment_item->property(SegmentItem::P_X_INI).toDouble(),
        segment_item->property(SegmentItem::P_Y_INI).toDouble(),
        segment_item->property(SegmentItem::P_X_FIN).toDouble(),
        segment_item->property(SegmentItem::P_Y_FIN).toDouble());
}

QPainterPath Segment::shape() const
{
    double x_m = (
        segment_item->property(SegmentItem::P_X_FIN).toDouble()
        - segment_item->property(SegmentItem::P_X_INI).toDouble());
    double y_m = (
        segment_item->property(SegmentItem::P_Y_FIN).toDouble()
        - segment_item->property(SegmentItem::P_Y_INI).toDouble());

    QPainterPath path;
    path.addRect(
        segment_item->property(SegmentItem::P_X_INI).toDouble(),
        segment_item->property(SegmentItem::P_X_FIN).toDouble(),
        segment_item->property(SegmentItem::P_Y_INI).toDouble(),
        segment_item->property(SegmentItem::P_Y_FIN).toDouble());
    return path;
}

QRectF Segment::boundingRect() const
{
    double x_m = (
        segment_item->property(SegmentItem::P_X_FIN).toDouble()
        - segment_item->property(SegmentItem::P_X_INI).toDouble());
    double y_m = (
        segment_item->property(SegmentItem::P_Y_FIN).toDouble()
        - segment_item->property(SegmentItem::P_Y_INI).toDouble());

    return QRectF(
        segment_item->property(SegmentItem::P_X_INI).toDouble(),
        segment_item->property(SegmentItem::P_X_FIN).toDouble(),
        segment_item->property(SegmentItem::P_Y_INI).toDouble(),
        segment_item->property(SegmentItem::P_Y_FIN).toDouble());
}

void Segment::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    _dragged = true;

    double delta_x = (
        segment_item->property(SegmentItem::P_X_FIN).toDouble()
        - segment_item->property(SegmentItem::P_X_INI).toDouble()) / 2;
    double delta_y = (
        segment_item->property(SegmentItem::P_Y_FIN).toDouble()
        - segment_item->property(SegmentItem::P_Y_INI).toDouble()) / 2;

    segment_item->setProperty(SegmentItem::P_X_INI, double(x()));
    segment_item->setProperty(SegmentItem::P_Y_INI, double(y()));
    segment_item->setProperty(SegmentItem::P_X_FIN, double(x()));
    segment_item->setProperty(SegmentItem::P_Y_FIN, double(y()));

    QGraphicsItem::mouseMoveEvent(event);
}

void Segment::addHandles(Handle* left_handle, Handle* right_handle)
{
    _left_handle = left_handle;
    _right_handle = right_handle;
}