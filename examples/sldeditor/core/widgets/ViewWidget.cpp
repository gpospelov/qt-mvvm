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

ViewWidget::ViewWidget(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(parent = this);
    setScene(scene);
    setRenderHints(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setContentsMargins(0,0,0,0);

    _axis = new AxisViewWidget();
    _axis->setParent(viewport());
    _axis->resize(size());
}


void ViewWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        scale(1.25, 1.25);
    else
        scale(0.8, 0.8);

    // _axis->resize();
}

void ViewWidget::drageMoveEvent(QDragMoveEvent *event)
{
    // _axis->resize();
    drageMoveEvent(event);
}

void ViewWidget::resizeEvent(QResizeEvent *event)
{
    _axis->resize(size());
}

QRectF ViewWidget::visibleRect()  const
{
    QPointF tl(horizontalScrollBar()->value(), verticalScrollBar()->value());
    QPointF br = tl + viewport()->rect().bottomRight();
    QMatrix mat = matrix().inverted();
    return mat.mapRect(QRectF(tl,br));
}
