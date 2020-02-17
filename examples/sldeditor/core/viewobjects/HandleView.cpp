// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "HandleView.h"
#include "HandleItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include <cmath>
#include <mvvm/plotting/sceneadapterinterface.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/utils/numericutils.h>

//! The constructor
HandleView::HandleView(HandleItem* item)
    : handle_item(item), color(item->property(HandleItem::P_COLOR).value<QColor>())
{
    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == HandleItem::P_XPOS) {
            update();
            emit moved();
        }
        if (property_name == HandleItem::P_YPOS) {
            update();
            emit moved();
        }
        if (property_name == HandleItem::P_COLOR) {
            color = handle_item->property(HandleItem::P_COLOR).value<QColor>();
            update();
        }
        if (property_name == HandleItem::P_RADIUS)
            update();
    };

    handle_item->mapper()->setOnPropertyChange(on_property_change, this);
    setZValue(20);
}

//! The overriden paint method
void HandleView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    auto adapter = getSceneAdapter();
    if (!adapter)
        return;

    ViewObject::paint(painter, nullptr, nullptr);

    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(
        QPointF(adapter->toSceneX(handle_item->property(HandleItem::P_XPOS).toDouble()),
                adapter->toSceneY(handle_item->property(HandleItem::P_YPOS).toDouble())),
        handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.,
        handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.);
}

//! The shape
QPainterPath HandleView::shape() const
{
    QPainterPath path;
    path.addRect(getSceneRect());
    return path;
}

//! The bounding rectangle of the handle
QRectF HandleView::boundingRect() const
{
    return getSceneRect();
}

//! Get the scene rectangle
QRectF HandleView::getSceneRect() const
{
    auto adapter = getSceneAdapter();
    if (!adapter)
        return QRectF(0, 0, 1, 1);

    return QRectF(
        QPointF(adapter->toSceneX(handle_item->property(HandleItem::P_XPOS).toDouble()
                                  - handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.),
                adapter->toSceneY(handle_item->property(HandleItem::P_YPOS).toDouble()
                                  + handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.)),
        QPointF(adapter->toSceneX(handle_item->property(HandleItem::P_XPOS).toDouble()
                                  + handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.),
                adapter->toSceneY(handle_item->property(HandleItem::P_YPOS).toDouble()
                                  - handle_item->property(HandleItem::P_RADIUS).toDouble() / 2.)));
}

//! On move update the model
void HandleView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    auto adapter = getSceneAdapter();
    if (!adapter)
        return;

    handle_item->setProperty(HandleItem::P_XPOS,
                             adapter->fromSceneX(double(x() + event->pos().x())));
    handle_item->setProperty(HandleItem::P_YPOS,
                             adapter->fromSceneY(double(y() + event->pos().y())));
}

//! Return a pointer to the handle item
HandleItem* HandleView::handleItem() const
{
    return handle_item;
}
