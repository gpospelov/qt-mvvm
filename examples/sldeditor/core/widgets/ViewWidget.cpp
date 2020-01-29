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

//! The constructor
ViewWidget::ViewWidget(QWidget* parent) : QGraphicsView(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(parent = this);
    setScene(scene);
    setRenderHints(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
    // scale(1.0, -1.0);
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
