// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapviewportplotcontroller.h"
#include "axisitems.h"
#include "viewportaxisplotcontroller.h"
#include "colormapviewportitem.h"
#include "colormapplotcontroller.h"
#include "colormapitem.h"
#include <list>
#include <qcustomplot.h>

using namespace ModelView;

struct ColorMapViewportPlotController::ColorMapViewportPlotControllerPrivate {
    ColorMapViewportPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    std::unique_ptr<ColorMapPlotController> colorMapController;
    std::unique_ptr<ViewportAxisPlotController> xAxisController;
    std::unique_ptr<ViewportAxisPlotController> yAxisController;

    ColorMapViewportPlotControllerPrivate(ColorMapViewportPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
        xAxisController = std::make_unique<ViewportAxisPlotController>(custom_plot->xAxis);
        yAxisController = std::make_unique<ViewportAxisPlotController>(custom_plot->yAxis);
        colorMapController = std::make_unique<ColorMapPlotController>(custom_plot);
    }

    ColorMapViewportItem* viewport_item() { return master->currentItem(); }

    //! Setup controller components.

    void setup_components()
    {
        auto viewport = viewport_item();
        xAxisController->setItem(viewport->xAxis());
        yAxisController->setItem(viewport->yAxis());
        auto colormap_item = viewport_item()->item<ColorMapItem>(ColorMapViewportItem::T_ITEMS);
        colorMapController->setItem(colormap_item);
        viewport_item()->update_viewport();
    }

    void unsubscribe_components() {
        xAxisController->setItem(nullptr);
        yAxisController->setItem(nullptr);
        colorMapController->setItem(nullptr);
    }
};

ColorMapViewportPlotController::ColorMapViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<ColorMapViewportPlotControllerPrivate>(this, custom_plot))
{
}

void ColorMapViewportPlotController::subscribe()
{
    auto on_row_inserted = [this](SessionItem*, std::string, int) {
        p_impl->setup_components();
    };
    currentItem()->mapper()->setOnRowInserted(on_row_inserted, this);


    p_impl->setup_components();
}

void ColorMapViewportPlotController::unsubscribe()
{
    p_impl->unsubscribe_components();
}

ColorMapViewportPlotController::~ColorMapViewportPlotController() = default;
