// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "elementview.h"
#include "graphicsscene.h"
#include "mvvm/plotting/sceneadapterinterface.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>

//! The constructor
ElementView::ElementView() : QGraphicsObject() 
{
    setAcceptHoverEvents(true);
}

ElementView::~ElementView() = default;

//! Get the conversion axes
ModelView::SceneAdapterInterface* ElementView::sceneAdapter() const
{
    GraphicsScene* scene_item = static_cast<GraphicsScene*>(scene());
    if (!scene_item)
        return nullptr;

    return scene_item->sceneAdapter();
}

//! Advance method used by the scene adapter
void ElementView::advance(int phase)
{
    if (!phase)
        return;
    prepareGeometryChange();
    update();
}

//! paint override
void ElementView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setClipRect(sceneAdapter()->viewportRectangle());
}

//! modify the rectangle for display according to the scene adapter
QRectF ElementView::displayRect(const QRectF &real_rect) const
{
    auto adapter = sceneAdapter();
    if (!adapter)
        return real_rect;

    auto output = QRectF(real_rect);

    if (m_center_based) {
        output = displayRectCenterBased(real_rect);
    } else {
        output = displayRectEdgeBased(real_rect);
    }

    if (m_stretch_left) {
        output = stretchRectLeft(output);
    } else if (m_stretch_right){
        output = stretchRectRight(output);
    }

    return output;
}

//! Helper function for displayRect based on the center of real_rect
QRectF ElementView::displayRectCenterBased(const QRectF &real_rect) const
{
    auto adapter = sceneAdapter();
    double x = real_rect.x();
    double y = real_rect.y();
    double w = real_rect.width();
    double h = real_rect.height();

    double center_x = x + w / 2.;
    double center_y = y + h / 2.;

    if (m_adapt_x) {
        center_x = adapter->toSceneX(-center_x);
    }
    if (m_adapt_y) {
        center_y = adapter->toSceneY(center_y);
    }
    if (m_adapt_width) {
        w = adapter->toSceneX(w) - adapter->toSceneX(0);
    }
    if (m_adapt_height) {
        h = adapter->toSceneY(h) - adapter->toSceneY(0);
    }

    x = center_x - w / 2;
    y = center_y - h / 2;

    return QRectF(x, y, w, h); 
}

//! Helper function for displayRect based on the edge of real_rect
QRectF ElementView::displayRectEdgeBased(const QRectF &real_rect) const
{
    auto adapter = sceneAdapter();
    double x = real_rect.x();
    double y = real_rect.y();
    double w = real_rect.width();
    double h = real_rect.height();

    if (m_adapt_x) {
        x = adapter->toSceneX(-x);
    }
    if (m_adapt_y) {
        y = adapter->toSceneY(y);
    }
    if (m_adapt_width) {
        w = adapter->toSceneX(w) - adapter->toSceneX(0);
    }
    if (m_adapt_height) {
        h = adapter->toSceneY(h) - adapter->toSceneY(0);
    }

    return QRectF(x, y, w, h);
}

//! Stretch the rectangle to the left limit of the viewport
QRectF ElementView::stretchRectLeft(const QRectF &real_rect) const
{
    auto adapter = sceneAdapter();
    double x_i = real_rect.x();
    double y_i = real_rect.y();
    double x_f = real_rect.x() + real_rect.width();
    double y_f = real_rect.y() + real_rect.height();

    auto viewport_rect = sceneAdapter()->viewportRectangle();
    x_i = viewport_rect.x();

    return QRectF(x_i, y_i, x_f - x_i, y_f - y_i);
}

//! Stretch the rectangle to the right limit of the viewport
QRectF ElementView::stretchRectRight(const QRectF &real_rect) const
{
    auto adapter = sceneAdapter();
    double x_i = real_rect.x();
    double y_i = real_rect.y();
    double x_f = real_rect.x() + real_rect.width();
    double y_f = real_rect.y() + real_rect.height();

    auto viewport_rect = sceneAdapter()->viewportRectangle();
    x_f = viewport_rect.x() + viewport_rect.width();

    return QRectF(x_i, y_i, x_f - x_i, y_f - y_i);
}


//! modify the path for display according to the scene adapter
QPainterPath ElementView::displayPath(QPainterPath real_path) const
{
    auto adapter = sceneAdapter();
    if (!adapter)
        return real_path;

    auto display_path = QPainterPath(real_path);
    for (int i = 0; i < display_path.elementCount(); i++) {
        QPointF pt = display_path.elementAt(i);
        display_path.setElementPositionAt(i, adapter->toSceneX(-pt.x()), adapter->toSceneY(pt.y()));
    }
    return display_path;
}

//! modify the rectangle for display according to the scene adapter
QPointF ElementView::scenePos(QPointF pixel_pos) const
{
    auto adapter = sceneAdapter();
    if (!adapter)
        return pixel_pos;

    return QPointF(-adapter->fromSceneX(pixel_pos.x()), adapter->fromSceneY(pixel_pos.y()));
}

//! Adapt the dimensions according to the center
void ElementView::setCenterBased(bool choice)
{
    m_center_based = choice;
}

//! Adapt the x position
void ElementView::adaptX(bool choice)
{
    m_adapt_x = choice;
}

//! Adapt the y position
void ElementView::adaptY(bool choice)
{
    m_adapt_y = choice;
}

//! Adapt the width
void ElementView::adaptW(bool choice)
{
    m_adapt_width = choice;
}

//! Adapt the height
void ElementView::adaptH(bool choice)
{
    m_adapt_height = choice;
}

//! Stretch the rectangle to the left limit of the viewport
void ElementView::stretchLeft(bool choice)
{
    m_stretch_left = choice;
}

//! Stretch the rectangle to the right limit of the viewport
void ElementView::stretchRight(bool choice)
{
    m_stretch_right = choice;
}

//! The hoover enter event
void ElementView::hoverEnterEvent (QGraphicsSceneHoverEvent *event)
{
    if (flags() & QGraphicsItem::ItemIsMovable)
        setCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsItem::hoverEnterEvent(event);
}

//! The hoover exit event
void ElementView::hoverLeaveEvent (QGraphicsSceneHoverEvent *event)
{
    unsetCursor();
    QGraphicsItem::hoverLeaveEvent(event);
}

//! The mouse press event
void ElementView::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    if (flags() & QGraphicsItem::ItemIsMovable)
        setCursor(QCursor(Qt::ClosedHandCursor));
    QGraphicsItem::mousePressEvent(event);
}

//! The mouse release event
void ElementView::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
    if (flags() & QGraphicsItem::ItemIsMovable)
        setCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsItem::mouseReleaseEvent(event);
}
