// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "handleelementview.h"
#include "layerelementcontroller.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

//! The constructor
HandleElementView::HandleElementView()
    : QGraphicsItem(), m_rectangle(QRectF(0, 0, 0, 0)), m_brush(QBrush()), m_pen(QPen()),
      m_pos(QPointF(0, 0))
{
    // setFlag(QGraphicsItem::ItemIsMovable);
}

//! The overriden paint method
void HandleElementView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRect(m_rectangle);
}

//! The shape
QPainterPath HandleElementView::shape() const
{
    QPainterPath path;
    path.addRect(m_rectangle);
    return path;
}

//! The bounding rectangle of the handle
QRectF HandleElementView::boundingRect() const
{
    return m_rectangle;
}

//! On move update the model
void HandleElementView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    m_pos = event->pos();
    p_controller->handleViewMoved(this);
}

//! Set the controller to report back the move
void HandleElementView::setLayerElementController(LayerElementController* controller)
{
    p_controller = controller;
}

//! Set the draw rectangle
void HandleElementView::setRectangle(QRectF rectangle)
{
    prepareGeometryChange();
    m_rectangle = rectangle;
}

//! Set the brush
void HandleElementView::setBrush(QBrush brush)
{
    m_brush = brush;
}

//! Set the pen
void HandleElementView::setPen(QPen pen)
{
    m_pen = pen;
}

//! Get the last position of the item
QPointF HandleElementView::getLastPos() const
{
    return m_pos;
}
