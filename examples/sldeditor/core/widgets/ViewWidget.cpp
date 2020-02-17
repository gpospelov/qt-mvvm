// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ViewWidget.h"
#include "GraphicsScene.h"

#include <memory>

//! The constructor
ViewWidget::ViewWidget(QWidget* parent) : QGraphicsView(parent), scale_factor(1., 1.)
{
    GraphicsScene* scene_item = new GraphicsScene(parent = this);
    setScene(scene_item);
    setRenderHints(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContentsMargins(0, 0, 0, 0);
}

void ViewWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    GraphicsScene* scene_item = static_cast<GraphicsScene*>(scene());
    scene_item->update_size(event->size());
}

GraphicsScene* ViewWidget::getScene() const
{
    return static_cast<GraphicsScene*>(scene());
}
