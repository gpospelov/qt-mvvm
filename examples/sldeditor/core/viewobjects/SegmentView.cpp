// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SegmentView.h"
#include "SegmentItem.h"

#include "HandleItem.h"
#include "HandleView.h"

#include "AxisObject.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsWidget>
#include <QPainter>
#include <QStyleOption>

#include <cmath>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

#include <iostream>

//! The constructor
SegmentView::SegmentView(SegmentItem* item)
    : segment_item(item), color(item->property(SegmentItem::P_COLOR).value<QColor>()),
      left_handle(nullptr), right_handle(nullptr)
{
    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == SegmentItem::P_X_POS) {
            AxisObject* axis = getAxes();
            setX(axis->fromRealToSceneX(segment_item->property(SegmentItem::P_X_POS).toDouble()));
        }
        if (property_name == SegmentItem::P_Y_POS) {
            AxisObject* axis = getAxes();
            setY(axis->fromRealToSceneY(segment_item->property(SegmentItem::P_Y_POS).toDouble()));
        }
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
    setFlag(QGraphicsItem::ItemIsMovable);
    setZValue(10);
}

//! The overriden paint method
void SegmentView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    AxisObject* axis = getAxes();
    if (!axis)
        return;

    painter->setBrush(color);
    painter->drawRect(getSceneRect());
}

//! The shape
QPainterPath SegmentView::shape() const
{
    QPainterPath path;

    AxisObject* axis = getAxes();
    if (!axis)
        return path;

    path.addRect(getSceneRect());

    return path;
}

//! The bounding rectangle of the handle
QRectF SegmentView::boundingRect() const
{
    double epsilon = 10;

    AxisObject* axis = getAxes();
    if (!axis)
        return QRectF(0, 0, 1, 1);

    return getSceneRect();
}

//! Get the scene rectangle
QRectF SegmentView::getSceneRect() const
{
    AxisObject* axis = getAxes();
    if (!axis)
        return QRectF(0, 0, 1, 1);

    return QRectF(
        QPointF(
            axis->fromRealToSceneX(-segment_item->property(SegmentItem::P_WIDTH).toDouble() / 2.),
            axis->fromRealToSceneY(+segment_item->property(SegmentItem::P_HEIGHT).toDouble() / 2.)),
        QPointF(
            axis->fromRealToSceneX(segment_item->property(SegmentItem::P_WIDTH).toDouble() / 2.),
            axis->fromRealToSceneY(-segment_item->property(SegmentItem::P_HEIGHT).toDouble()
                                   / 2.)));
}

//! On move update the model
void SegmentView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    AxisObject* axis = getAxes();
    if (!axis)
        return;

    if (segment_item->property(SegmentItem::P_HORIZONTAL).toBool())
        if (axis->fromSceneToRealY(double(y() + event->pos().y())) > 0)
            segment_item->setProperty(SegmentItem::P_Y_POS,
                                      axis->fromSceneToRealY(double(y() + event->pos().y())));
        else
            return;
    else
        segment_item->setProperty(SegmentItem::P_X_POS,
                                  axis->fromSceneToRealX(double(x() + event->pos().x())));

    moveHandles();
}

//! Add the handles at the end
void SegmentView::addHandles(HandleView* left_handle_in, HandleView* right_handle_in)
{
    left_handle = left_handle_in;
    right_handle = right_handle_in;

    connectHandles();
    moveHandles();
}

//! Connect the handles
void SegmentView::connectHandles()
{
    connect(left_handle, &HandleView::moved, this, &SegmentView::refreshFromLeftHandle);

    connect(right_handle, &HandleView::moved, this, &SegmentView::refreshFromRightHandle);
}

//! Disconnect the handle signaling
void SegmentView::disconnectHandles()
{
    disconnect(left_handle, &HandleView::moved, this, &SegmentView::refreshFromLeftHandle);

    disconnect(right_handle, &HandleView::moved, this, &SegmentView::refreshFromRightHandle);
}

//! Refresh the properties from the handle info
void SegmentView::refreshFromLeftHandle()
{
    if (!left_handle)
        return;
    if (!right_handle)
        return;

    AxisObject* axis = getAxes();
    if (!axis)
        return;

    double left_x = left_handle->handleItem()->property(HandleItem::P_XPOS).toDouble();
    double left_y = left_handle->handleItem()->property(HandleItem::P_YPOS).toDouble();
    double right_x = right_handle->handleItem()->property(HandleItem::P_XPOS).toDouble();
    double right_y = right_handle->handleItem()->property(HandleItem::P_YPOS).toDouble();

    if (segment_item->property(SegmentItem::P_HORIZONTAL).toBool()) {
        segment_item->setProperty(SegmentItem::P_X_POS,
                                  segment_item->property(SegmentItem::P_WIDTH).toDouble() / 2.
                                      + left_x);
        segment_item->setProperty(SegmentItem::P_Y_POS, left_y);
    } else {
        segment_item->setProperty(SegmentItem::P_X_POS, left_x);
        segment_item->setProperty(SegmentItem::P_Y_POS, (right_y - left_y) / 2. + left_y);
        segment_item->setProperty(SegmentItem::P_HEIGHT, (right_y - left_y));
    }
    moveHandles();
}

//! Refresh the properties from the handle info
void SegmentView::refreshFromRightHandle()
{
    if (!left_handle)
        return;
    if (!right_handle)
        return;

    AxisObject* axis = getAxes();
    if (!axis)
        return;

    double left_x = left_handle->handleItem()->property(HandleItem::P_XPOS).toDouble();
    double left_y = left_handle->handleItem()->property(HandleItem::P_YPOS).toDouble();
    double right_x = right_handle->handleItem()->property(HandleItem::P_XPOS).toDouble();
    double right_y = right_handle->handleItem()->property(HandleItem::P_YPOS).toDouble();

    if (segment_item->property(SegmentItem::P_HORIZONTAL).toBool()) {
        if ((right_x - left_x) <= 0) {
            right_handle->handleItem()->setProperty(HandleItem::P_XPOS, left_x + 1.);
            refreshFromRightHandle();
        } else {
            segment_item->setProperty(SegmentItem::P_WIDTH, (right_x - left_x));
            segment_item->setProperty(SegmentItem::P_X_POS,
                                      segment_item->property(SegmentItem::P_WIDTH).toDouble() / 2.
                                          + left_x);
            segment_item->setProperty(SegmentItem::P_Y_POS, left_y);
        }

    } else {
        segment_item->setProperty(SegmentItem::P_X_POS, left_x);
        segment_item->setProperty(SegmentItem::P_Y_POS, (right_y - left_y) / 2. + left_y);
        segment_item->setProperty(SegmentItem::P_HEIGHT, (right_y - left_y));
    }
    moveHandles();
}

//! Move the linked handles
void SegmentView::moveHandles()
{
    if (!left_handle)
        return;
    if (!right_handle)
        return;

    AxisObject* axis = getAxes();
    if (!axis)
        return;

    if (segment_item->property(SegmentItem::P_HORIZONTAL).toBool()) {

        double x_pos = 0.;
        double y_pos = 0.;
        HandleItem* item;

        x_pos = (segment_item->property(SegmentItem::P_X_POS).toDouble()
                 - segment_item->property(SegmentItem::P_WIDTH).toDouble() / 2);

        y_pos = (segment_item->property(SegmentItem::P_Y_POS).toDouble());

        item = left_handle->handleItem();
        item->setProperty(HandleItem::P_XPOS, x_pos);
        item->setProperty(HandleItem::P_YPOS, y_pos);

        x_pos = (segment_item->property(SegmentItem::P_X_POS).toDouble()
                 + segment_item->property(SegmentItem::P_WIDTH).toDouble() / 2);

        y_pos = (segment_item->property(SegmentItem::P_Y_POS).toDouble());

        item = right_handle->handleItem();
        item->setProperty(HandleItem::P_XPOS, x_pos);
        item->setProperty(HandleItem::P_YPOS, y_pos);

    } else {

        double x_pos = 0.;
        double y_pos = 0.;
        HandleItem* item;

        x_pos = (segment_item->property(SegmentItem::P_X_POS).toDouble());

        y_pos = (segment_item->property(SegmentItem::P_Y_POS).toDouble()
                 - segment_item->property(SegmentItem::P_HEIGHT).toDouble() / 2);

        item = left_handle->handleItem();
        item->setProperty(HandleItem::P_XPOS, x_pos);
        item->setProperty(HandleItem::P_YPOS, y_pos);

        x_pos = (segment_item->property(SegmentItem::P_X_POS).toDouble());

        y_pos = (segment_item->property(SegmentItem::P_Y_POS).toDouble()
                 + segment_item->property(SegmentItem::P_HEIGHT).toDouble() / 2);

        item = right_handle->handleItem();
        item->setProperty(HandleItem::P_XPOS, x_pos);
        item->setProperty(HandleItem::P_YPOS, y_pos);
    }
}

SegmentItem* SegmentView::segmentItem() const
{
    return segment_item;
}
