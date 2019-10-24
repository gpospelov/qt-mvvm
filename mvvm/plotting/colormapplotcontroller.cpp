// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapplotcontroller.h"
#include "colormapitem.h"
#include "data2ditem.h"
#include "data2dplotcontroller.h"
#include "qcustomplot.h"

using namespace ModelView;

struct ColorMapPlotController::ColorMapPlotControllerPrivate {
    ColorMapPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    QCPColorMap* color_map{nullptr};
    std::unique_ptr<Data2DPlotController> data_controller;

    ColorMapPlotControllerPrivate(ColorMapPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

    ~ColorMapPlotControllerPrivate() {
        if (color_map)
            custom_plot->removePlottable(color_map);
    }

    ColorMapItem* colormap_item() { return master->currentItem(); }

    void create_colormap()
    {
        if (color_map)
            throw std::runtime_error("ColorMap is already defined");

        color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);

        create_data_controller();

        update_interpolation();
    }

    void update_interpolation()
    {
        auto is_interpolated = colormap_item()->property(ColorMapItem::P_INTERPOLATION).toBool();
        color_map->setInterpolate(is_interpolated);
        custom_plot->replot();
    }

    void create_data_controller()
    {
        if (!data_controller)
            data_controller = std::make_unique<Data2DPlotController>(color_map);
        data_controller->setItem(colormap_item()->dataItem());
    }

    void remove_colormap()
    {
        if (!color_map)
            throw std::runtime_error("No colormap defined");

        data_controller.reset();
        custom_plot->removePlottable(color_map);
        color_map = nullptr;
    }

};

ColorMapPlotController::ColorMapPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<ColorMapPlotControllerPrivate>(this, custom_plot))
{
}

void ColorMapPlotController::subscribe()
{
    auto on_property_change = [this](SessionItem*, std::string property_name) {
        if (property_name == ColorMapItem::P_INTERPOLATION)
            p_impl->update_interpolation();

        if (property_name == ColorMapItem::P_LINK)
            p_impl->create_data_controller();
    };
    currentItem()->mapper()->setOnPropertyChange(on_property_change, this);

    p_impl->create_colormap();
}

void ColorMapPlotController::unsubscribe()
{
    p_impl->remove_colormap();
}

ColorMapPlotController::~ColorMapPlotController() = default;
