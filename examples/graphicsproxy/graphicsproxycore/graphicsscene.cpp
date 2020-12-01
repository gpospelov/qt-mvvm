// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsscene.h"
#include "axesrectangleview.h"
#include "regionofinterestview.h"
#include <mvvm/plotting/colormapcanvas.h>
#include <mvvm/plotting/customplotproxywidget.h>
#include <mvvm/plotting/sceneadapterinterface.h>

namespace
{
const double scene_origin_x{0.0};
const double scene_origin_y{0.0};
const QRectF default_scene_rect{QPointF{scene_origin_x, scene_origin_y}, QSizeF{800, 600}};
} // namespace

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent)
{
    setSceneRect(default_scene_rect);
}

void GraphicsScene::setContext(ModelView::ColorMapCanvas* colormap, RegionOfInterestItem* roi)
{
    clear();
    create_colormap_proxy(colormap);
    create_roi_view(roi);
}

GraphicsScene::~GraphicsScene() = default;

//! Adjust size of scene and color map proxy.

void GraphicsScene::update_size(const QSize& newSize)
{
    if (colormap_proxy) {
        colormap_proxy->resize(newSize);
        setSceneRect(scene_origin_x, scene_origin_y, newSize.width(), newSize.height());
        colormap_proxy->setPos(0.0, 0.0);
        advance(); // notifies all QGraphicsItem that it is time to replot themself using new status
                   // of scene adapter
    }
}

void GraphicsScene::create_colormap_proxy(ModelView::ColorMapCanvas* colormap)
{
    scene_adapter = colormap->createSceneAdapter();
    colormap_proxy = new ModelView::CustomPlotProxyWidget(colormap);
    addItem(colormap_proxy);
}

//! Creates parent object AxesRectangleView to hold single child RegionOfInterestView.
//! AxesRectangleView serves as an invisible clipping rectangle to hide parts of children
//! when they go out of axes rectangle at current zoom level.

void GraphicsScene::create_roi_view(RegionOfInterestItem* roi_item)
{
    auto axes_view = new AxesRectangleView(scene_adapter.get());
    auto roi_view = new RegionOfInterestView(roi_item, scene_adapter.get());
    roi_view->setParentItem(axes_view);
    addItem(axes_view);
}
