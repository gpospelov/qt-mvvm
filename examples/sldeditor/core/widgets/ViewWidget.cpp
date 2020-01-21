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

ViewWidget::ViewWidget(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(-500,-500,1000,1000,parent = this);
    this->setScene(scene);
    setRenderHints(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
}


void ViewWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        scale(1.25, 1.25);
    else
        scale(0.8, 0.8);
}

void ViewWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        rotate(1);
    else if(event->key() == Qt::Key_Right)
        rotate(-1);
}