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
#include "axisplotcontrollers.h"
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
    std::unique_ptr<AxisPlotController> xAxisController;
    std::unique_ptr<AxisPlotController> yAxisController;

    ColorMapViewportPlotControllerPrivate(ColorMapViewportPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

    ColorMapViewportItem* viewport_item() { return master->currentItem(); }

    //! Setup controller components.

    void setup_components()
    {
        create_axis_controllers();
        create_colormap_controller();
    }


    //! Creates x,y axes controllers.

    void create_axis_controllers()
    {
        auto viewport = viewport_item();

        xAxisController = std::make_unique<XAxisPlotController>(custom_plot);
        xAxisController->setItem(viewport->xAxis());

        yAxisController = std::make_unique<YAxisPlotController>(custom_plot);
        yAxisController->setItem(viewport->yAxis());
    }

    //! Creates colormap controller.

    void create_colormap_controller()
    {
        colorMapController = std::make_unique<ColorMapPlotController>(custom_plot);
        auto colormap_item = viewport_item()->item<ColorMapItem>(ColorMapViewportItem::T_ITEMS);
        colorMapController->setItem(colormap_item);
        viewport_item()->update_viewport();
    }
};

ColorMapViewportPlotController::ColorMapViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<ColorMapViewportPlotControllerPrivate>(this, custom_plot))
{
}

void ColorMapViewportPlotController::subscribe()
{
    p_impl->setup_components();
}

ColorMapViewportPlotController::~ColorMapViewportPlotController() = default;
