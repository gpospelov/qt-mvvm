// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/plotting/colormapviewportplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/plotting/viewportaxisplotcontroller.h>
#include <mvvm/standarditems/colormapviewportitem.h>
#include <mvvm/plotting/colormapplotcontroller.h>
#include <mvvm/standarditems/colormapitem.h>
#include <mvvm/plotting/colorscaleplotcontroller.h>
#include <list>
#include <qcustomplot.h>

using namespace ModelView;

struct ColorMapViewportPlotController::ColorMapViewportPlotControllerImpl {
    ColorMapViewportPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    QCPColorScale* color_scale{nullptr};
    std::unique_ptr<ViewportAxisPlotController> xAxisController;
    std::unique_ptr<ViewportAxisPlotController> yAxisController;
    std::unique_ptr<ColorScalePlotController> colorScaleController;
    std::unique_ptr<ColorMapPlotController> colorMapController;

    ColorMapViewportPlotControllerImpl(ColorMapViewportPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot), color_scale(new QCPColorScale(custom_plot))
    {
        xAxisController = std::make_unique<ViewportAxisPlotController>(custom_plot->xAxis);
        yAxisController = std::make_unique<ViewportAxisPlotController>(custom_plot->yAxis);
        colorScaleController = std::make_unique<ColorScalePlotController>(color_scale);
        colorMapController = std::make_unique<ColorMapPlotController>(custom_plot, color_scale);
    }

    ColorMapViewportItem* viewport_item() { return master->currentItem(); }

    //! Setup controller components.

    void setup_components()
    {
        auto viewport = viewport_item();
        xAxisController->setItem(viewport->xAxis());
        yAxisController->setItem(viewport->yAxis());
        colorScaleController->setItem(viewport->zAxis());
        auto colormap_item = viewport_item()->item<ColorMapItem>(ColorMapViewportItem::T_ITEMS);
        colorMapController->setItem(colormap_item);
        viewport_item()->update_viewport();
    }

    void unsubscribe_components() {
        xAxisController->setItem(nullptr);
        yAxisController->setItem(nullptr);
        colorScaleController->setItem(nullptr);
        colorMapController->setItem(nullptr);
    }
};

ColorMapViewportPlotController::ColorMapViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<ColorMapViewportPlotControllerImpl>(this, custom_plot))
{
}

void ColorMapViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](SessionItem*, TagRow) {
        p_impl->setup_components();
    };
    currentItem()->mapper()->setOnItemInserted(on_item_inserted, this);


    p_impl->setup_components();
}

void ColorMapViewportPlotController::unsubscribe()
{
    p_impl->unsubscribe_components();
}

ColorMapViewportPlotController::~ColorMapViewportPlotController() = default;
