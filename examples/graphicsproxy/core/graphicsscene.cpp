// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsscene.h"
#include "colormapproxywidget.h"
#include "regionofinterestview.h"
#include <mvvm/plotting/sceneadapterinterface.h>
#include <mvvm/plotting/colormapcanvas.h>
#include <QDebug>

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

GraphicsScene::~GraphicsScene() = default;

void GraphicsScene::setColorMap(ModelView::ColorMapCanvas* colormap)
{
    clear();
    scene_adapter = colormap->createSceneAdapter();
    colormap_proxy = new ColorMapProxyWidget(colormap);
    addItem(colormap_proxy);
}

void GraphicsScene::setRegionOfInterest(RegionOfInterestItem* roi)
{
    addItem(new RegionOfInterestView(roi));
}

//! Adjust size of scene and color map proxy.

void GraphicsScene::update_size(const QSize& newSize)
{
    if (colormap_proxy) {
        colormap_proxy->resize(newSize);
        setSceneRect(scene_origin_x, scene_origin_y, newSize.width(), newSize.height());
        colormap_proxy->setPos(0.0, 0.0);
    }
}
