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
#include <QGraphicsSceneMouseEvent>

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
        if (property_name == SegmentItem::P_X_POS)
            setX(segment_item->property(SegmentItem::P_X_POS).toDouble());
        if (property_name == SegmentItem::P_Y_POS)
            setY(segment_item->property(SegmentItem::P_Y_POS).toDouble());
        if (property_name == SegmentItem::P_HEIGHT)
            update();
        if (property_name == SegmentItem::P_WIDTH)
            update();
        if (property_name == SegmentItem::P_HORIZONTAL)
            update();
        if (property_name == SegmentItem::P_COLOR)
            update();
    };
    segment_item->mapper()->setOnPropertyChange(on_property_change, this);

    setPos(
        segment_item->property(SegmentItem::P_X_POS).toDouble(),
        segment_item->property(SegmentItem::P_Y_POS).toDouble()
    );

    setFlag(QGraphicsItem::ItemIsMovable);

}

void Segment::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setBrush(color);
    painter->drawRect(
        - segment_item->property(SegmentItem::P_WIDTH).toDouble()/2,
        - segment_item->property(SegmentItem::P_HEIGHT).toDouble()/2,
        segment_item->property(SegmentItem::P_WIDTH).toDouble(),
        segment_item->property(SegmentItem::P_HEIGHT).toDouble());
}

QPainterPath Segment::shape() const
{
    QPainterPath path;
    path.addRect(
        - segment_item->property(SegmentItem::P_WIDTH).toDouble()/2,
        - segment_item->property(SegmentItem::P_HEIGHT).toDouble()/2,
        segment_item->property(SegmentItem::P_WIDTH).toDouble(),
        segment_item->property(SegmentItem::P_HEIGHT).toDouble());

    return path;
}

QRectF Segment::boundingRect() const
{
    return QRectF(
        - segment_item->property(SegmentItem::P_WIDTH).toDouble()/2,
        - segment_item->property(SegmentItem::P_HEIGHT).toDouble()/2,
        segment_item->property(SegmentItem::P_WIDTH).toDouble(),
        segment_item->property(SegmentItem::P_HEIGHT).toDouble());
}

void Segment::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    _dragged = true;

    segment_item->setProperty(SegmentItem::P_X_POS, double(x()+ event->pos().x()));
    segment_item->setProperty(SegmentItem::P_Y_POS, double(y()+ event->pos().y()));

    // QGraphicsItem::mouseMoveEvent(event);
}

void Segment::addHandles(Handle* left_handle, Handle* right_handle)
{
    _left_handle = left_handle;
    _right_handle = right_handle;
}