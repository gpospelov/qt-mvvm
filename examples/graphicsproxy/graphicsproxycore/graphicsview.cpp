// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsview.h"
#include "graphicsscene.h"
#include <QResizeEvent>

GraphicsView::GraphicsView(GraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent), scene(scene)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//! Notifies scene about size change.

void GraphicsView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    scene->update_size(event->size());
}
