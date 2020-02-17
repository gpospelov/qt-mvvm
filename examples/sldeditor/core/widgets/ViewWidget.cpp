// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ViewWidget.h"
#include <QGraphicsScene>
#include <QLayout>
#include <QScrollBar>

#include <iostream>

//! The constructor
ViewWidget::ViewWidget(QWidget* parent) : QGraphicsView(parent), scale_factor(1., 1.)
{
    QGraphicsScene* scene = new QGraphicsScene(parent = this);
    setScene(scene);
    setRenderHints(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setContentsMargins(0, 0, 0, 0);

    axis = new AxisViewWidget();
    axis->setParent(viewport());
    axis->resize(size());
}

//! Manage wheelevent
void ViewWidget::wheelEvent(QWheelEvent* event)
{
    if (event->delta() > 0)
        scale(1.25, 1.25);
    else
        scale(0.8, 0.8);

    axis->resize(size());
}

//! The resize event that needs to propagate to axes
void ViewWidget::resizeEvent(QResizeEvent* event)
{
    axis->resize(size());
    QGraphicsView::resizeEvent(event);
}

//! Get the visible region
QRectF ViewWidget::visibleRect() const
{
    QPointF tl(horizontalScrollBar()->value(), verticalScrollBar()->value());
    QPointF br = tl + viewport()->rect().bottomRight();
    QMatrix mat = matrix().inverted();
    return mat.mapRect(QRectF(tl, br));
}

//! Get the axis
AxisViewWidget* ViewWidget::getAxisView() const
{
    return axis;
}

//! Manage wheelevent
void ViewWidget::mouseMoveEvent(QMouseEvent* event)
{
    Qt::MouseButtons buttons = event->buttons();

    if (buttons & Qt::LeftButton) {
        QGraphicsView::mouseMoveEvent(event);
    } else if (buttons & Qt::RightButton) {
        rescaleScene(event);
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

//! Manage Press events
void ViewWidget::mousePressEvent(QMouseEvent* event)
{
    Qt::MouseButtons buttons = event->buttons();

    if (buttons & Qt::LeftButton) {
        QGraphicsView::mousePressEvent(event);
    } else if (buttons & Qt::RightButton) {
        init_mouse_pos = event->pos();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

//! Interface with releasevents
void ViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

//! Manage the mouse rescale routine
void ViewWidget::rescaleScene(QMouseEvent* event)
{
    scale_factor.setX(0.01 * (event->pos().x() - init_mouse_pos.x()) + 1);
    scale_factor.setY(0.01 * (event->pos().y() - init_mouse_pos.y()) + 1);
    scale(scale_factor.x(), scale_factor.y());
    init_mouse_pos.setX(event->pos().x());
    init_mouse_pos.setY(event->pos().y());
}
