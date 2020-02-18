// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //
#include "RoughnessView.h"
#include "RoughnessItem.h"

#include "HandleItem.h"
#include "HandleView.h"
#include "SegmentItem.h"
#include "SegmentView.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsWidget>
#include <QPainter>
#include <QStyleOption>

#include <cmath>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/plotting/sceneadapterinterface.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

//! The constructor
RoughnessView::RoughnessView(RoughnessItem* item) : roughness_item(item)
{
    HandleItem* right_handle_item = item->model()->insertItem<HandleItem>();
    HandleItem* left_handle_item = item->model()->insertItem<HandleItem>();

    right_handle = new HandleView(right_handle_item);
    left_handle = new HandleView(left_handle_item);

    right_handle->setFlag(QGraphicsItem::ItemIsMovable);
    left_handle->setFlag(QGraphicsItem::ItemIsMovable);

    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == RoughnessItem::P_ROUGHNESS) {
            update();
            // moveHandles();
        }
    };

    roughness_item->mapper()->setOnPropertyChange(on_property_change, this);

    setZValue(30);
}

//! The overriden paint method
void RoughnessView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    auto adapter = getSceneAdapter();
    if (!adapter)
        return;

    ViewObject::paint(painter, nullptr, nullptr);

    auto pen = QPen(Qt::PenStyle::DashLine);
    pen.setColor(roughness_item->property(RoughnessItem::P_COLOR).value<QColor>());

    painter->setPen(pen);
    painter->drawPath(getPath());

    if (!right_handle->scene()) {
        scene()->addItem(right_handle);
        right_handle->update();
    }
    if (!left_handle->scene()) {
        scene()->addItem(left_handle);
        left_handle->update();
    }
}

//! The shape
QPainterPath RoughnessView::shape() const
{
    QPainterPath path;
    path.addPath(getPath());
    return path;
}

//! The bounding rectangle of the handle
QRectF RoughnessView::boundingRect() const
{
    double epsilon = 10;

    auto adapter = getSceneAdapter();
    if (!adapter)
        return QRectF(0, 0, 1, 1);

    return QRectF(0, 0, 1, 1); // getPath().boundingRect();
}

//! Get the scene rectangle
QPainterPath RoughnessView::getPath() const
{
    auto adapter = getSceneAdapter();
    if (!adapter)
        return QPainterPath();

    if (!left_segment || !middle_segment || !right_segment)
        return QPainterPath();

    double roughness = roughness_item->property(RoughnessItem::P_ROUGHNESS).toDouble();

    double width_left = left_segment->segmentItem()->property(SegmentItem::P_WIDTH).toDouble();
    double width_mid = middle_segment->segmentItem()->property(SegmentItem::P_WIDTH).toDouble();
    double width_right = right_segment->segmentItem()->property(SegmentItem::P_WIDTH).toDouble();

    double height_left = left_segment->segmentItem()->property(SegmentItem::P_HEIGHT).toDouble();
    double height_mid = middle_segment->segmentItem()->property(SegmentItem::P_HEIGHT).toDouble();
    double height_right = right_segment->segmentItem()->property(SegmentItem::P_HEIGHT).toDouble();

    double pos_x = middle_segment->segmentItem()->property(SegmentItem::P_X_POS).toDouble();
    double pos_y = middle_segment->segmentItem()->property(SegmentItem::P_Y_POS).toDouble();
    double comp_left = left_segment->segmentItem()->property(SegmentItem::P_Y_POS).toDouble();
    double comp_right = right_segment->segmentItem()->property(SegmentItem::P_Y_POS).toDouble();

    auto path = QPainterPath();

    if (comp_left > comp_right) {
        path.moveTo(adapter->toSceneX(pos_x - roughness),
                    adapter->toSceneY(pos_y - height_mid / 2.) + height_left / 2.);
        path.lineTo(adapter->toSceneX(pos_x - roughness),
                    adapter->toSceneY(pos_y + height_mid / 2.));
        path.lineTo(adapter->toSceneX(pos_x)
                        - middle_segment->rightHandle()
                                  ->handleItem()
                                  ->property(HandleItem::P_RADIUS)
                                  .toDouble()
                              / 2.,
                    adapter->toSceneY(pos_y + height_mid / 2.));

        path.moveTo(adapter->toSceneX(pos_x + roughness),
                    adapter->toSceneY(pos_y + height_mid / 2.) - height_right / 2.);
        path.lineTo(adapter->toSceneX(pos_x + roughness),
                    adapter->toSceneY(pos_y - height_mid / 2.));
        path.lineTo(adapter->toSceneX(pos_x)
                        + middle_segment->leftHandle()
                                  ->handleItem()
                                  ->property(HandleItem::P_RADIUS)
                                  .toDouble()
                              / 2.,
                    adapter->toSceneY(pos_y - height_mid / 2.));
    } else {
        path.moveTo(adapter->toSceneX(pos_x - roughness),
                    adapter->toSceneY(pos_y - height_mid / 2.) - height_left / 2.);
        path.lineTo(adapter->toSceneX(pos_x - roughness),
                    adapter->toSceneY(pos_y + height_mid / 2.));
        path.lineTo(adapter->toSceneX(pos_x)
                        - middle_segment->leftHandle()
                                  ->handleItem()
                                  ->property(HandleItem::P_RADIUS)
                                  .toDouble()
                              / 2.,
                    adapter->toSceneY(pos_y + height_mid / 2.));

        path.moveTo(adapter->toSceneX(pos_x + roughness),
                    adapter->toSceneY(pos_y + height_mid / 2.) + height_right / 2.);
        path.lineTo(adapter->toSceneX(pos_x + roughness),
                    adapter->toSceneY(pos_y - height_mid / 2.));
        path.lineTo(adapter->toSceneX(pos_x)
                        + middle_segment->rightHandle()
                                  ->handleItem()
                                  ->property(HandleItem::P_RADIUS)
                                  .toDouble()
                              / 2.,
                    adapter->toSceneY(pos_y - height_mid / 2.));
    }
    return path;
}

//! Set the segments of this item
void RoughnessView::setSegments(SegmentView* left_segment_in, SegmentView* middle_segment_in,
                                SegmentView* right_segment_in)
{
    left_segment = left_segment_in;
    middle_segment = middle_segment_in;
    right_segment = right_segment_in;

    connectSegments();
}

//! Connect the handles
void RoughnessView::connectSegments()
{
    connect(left_segment, &SegmentView::moved, this, &RoughnessView::refreshFromSegments);

    connect(middle_segment, &SegmentView::moved, this, &RoughnessView::refreshFromSegments);

    connect(right_segment, &SegmentView::moved, this, &RoughnessView::refreshFromSegments);
}

//! Disconnect the handle signaling
void RoughnessView::disconnectSegments()
{
    disconnect(left_segment, &SegmentView::moved, this, &RoughnessView::refreshFromSegments);

    disconnect(middle_segment, &SegmentView::moved, this, &RoughnessView::refreshFromSegments);

    disconnect(right_segment, &SegmentView::moved, this, &RoughnessView::refreshFromSegments);
}

//! Refresh the properties from the handle info
void RoughnessView::refreshFromSegments()
{
    if (!left_segment)
        return;
    if (!middle_segment)
        return;
    if (!right_segment)
        return;

    return;
}

RoughnessItem* RoughnessView::roughnessItem() const
{
    return roughness_item;
}

void RoughnessView::moveHandles() {}
