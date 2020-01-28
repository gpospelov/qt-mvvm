// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "AxisViewWidget.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsSceneMouseEvent>

#include <iostream>


AxisViewWidget::AxisViewWidget() : QGraphicsView()
{
    QGraphicsScene* scene_item = new QGraphicsScene();
    setScene(scene_item);
    setRenderHints(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setAttribute( Qt::WA_TransparentForMouseEvents );
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("border-width: 0px; border-style: solid;background: transparent");

    _axis_object = new AxisObject();
    scene()->addItem(_axis_object);
}

void AxisViewWidget::resize(const QSize size)
{
    QWidget::resize(size.width(), size.height());
    scene()->setSceneRect(0,0,size.width(), size.height());
    update();

}

AxisObject* AxisViewWidget::getAxisObject() const
{
    return _axis_object;
}
