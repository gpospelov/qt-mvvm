// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapplotcontroller.h"
#include "data2ditem.h"
#include "colormapitem.h"
#include "qcustomplot.h"

using namespace ModelView;

struct ColorMapPlotController::ColorMapPlotControllerPrivate {
    ColorMapPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    QCPColorMap* color_map{nullptr};

    ColorMapPlotControllerPrivate(ColorMapPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

    ~ColorMapPlotControllerPrivate() {
        if (color_map)
            custom_plot->removePlottable(color_map);
    }

    ColorMapItem* colormap_item() { return master->currentItem(); }

};

ColorMapPlotController::ColorMapPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<ColorMapPlotControllerPrivate>(this, custom_plot))
{
}

void ColorMapPlotController::subscribe()
{
}

void ColorMapPlotController::unsubscribe()
{
}

ColorMapPlotController::~ColorMapPlotController() = default;
