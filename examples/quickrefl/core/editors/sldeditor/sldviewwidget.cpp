// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sldviewwidget.h"
#include "applicationmodels.h"
#include "graphicsscene.h"
#include "sldelementcontroller.h"
#include <QResizeEvent>

//! The constructor
SLDViewWidget::SLDViewWidget(ApplicationModels* app_models, QWidget* parent)
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

    m_sld_controller = std::make_unique<SLDElementController>(
            app_models->materialModel(), app_models->sampleModel(), app_models->sldViewModel(), nullptr);
    m_sld_controller->setScene(scene_item);
}

//! The destructor
SLDViewWidget::~SLDViewWidget() = default;

//! Resize event management
void SLDViewWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    GraphicsScene* scene_item = static_cast<GraphicsScene*>(scene());
    scene_item->update_size(event->size());
}
