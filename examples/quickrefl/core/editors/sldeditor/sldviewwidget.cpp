// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sldviewwidget.h"
#include "graphicsscene.h"
#include "sldelementcontroller.h"

#include <memory>

//! The constructor
SLDViewWidget::SLDViewWidget(SLDElementController* sld_controller, QWidget* parent)
    : QGraphicsView(parent)
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

    sld_controller->setScene(scene_item);
}

//! Resize event management
void SLDViewWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    GraphicsScene* scene_item = static_cast<GraphicsScene*>(scene());
    scene_item->update_size(event->size());
}

//! dynamic cast implementation of the get scene into the right object
GraphicsScene* SLDViewWidget::getScene() const
{
    return static_cast<GraphicsScene*>(scene());
}
