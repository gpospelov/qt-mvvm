// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/colormapplotcontroller.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/plotting/data2dplotcontroller.h"
#include "mvvm/standarditems/colormapitem.h"
#include "mvvm/standarditems/data2ditem.h"
#include <qcustomplot.h>
#include <map>
#include <memory>
#include <string>

namespace {
using gradient_map_t = std::map<std::string, QCPColorGradient::GradientPreset>;
gradient_map_t createGradientMap()
{
    gradient_map_t result;

    result["Grayscale"] = QCPColorGradient::gpGrayscale;
    result["Hot"] = QCPColorGradient::gpHot;
    result["Cold"] = QCPColorGradient::gpCold;
    result["Night"] = QCPColorGradient::gpNight;
    result["Candy"] = QCPColorGradient::gpCandy;
    result["Geography"] = QCPColorGradient::gpGeography;
    result["Ion"] = QCPColorGradient::gpIon;
    result["Thermal"] = QCPColorGradient::gpThermal;
    result["Polar"] = QCPColorGradient::gpPolar;
    result["Spectrum"] = QCPColorGradient::gpSpectrum;
    result["Jet"] = QCPColorGradient::gpJet;
    result["Hues"] = QCPColorGradient::gpHues;

    return result;
}

QCPColorGradient getGradient(const std::string& gradientName)
{
    static gradient_map_t gradient_map = createGradientMap();
    auto it = gradient_map.find(gradientName);
    return it != gradient_map.end() ? QCPColorGradient(it->second) : QCPColorGradient::gpSpectrum;
}

} // namespace

using namespace ModelView;

struct ColorMapPlotController::ColorMapPlotControllerImpl {
    ColorMapPlotController* m_master{nullptr};
    QCustomPlot* m_custom_plot{nullptr};
    QCPColorMap* m_color_map{nullptr};
    std::unique_ptr<Data2DPlotController> m_data_controller;

    ColorMapPlotControllerImpl(ColorMapPlotController* master, QCustomPlot* plot,
                               QCPColorScale* color_scale)
        : m_master(master), m_custom_plot(plot)
    {
        m_color_map = new QCPColorMap(m_custom_plot->m_xAxis, m_custom_plot->m_yAxis);
        m_data_controller = std::make_unique<Data2DPlotController>(m_color_map);

        if (color_scale)
            m_color_map->setColorScale(color_scale);
    }

    ~ColorMapPlotControllerImpl() { m_custom_plot->removePlottable(m_color_map); }

    ColorMapItem* colormap_item() { return m_master->currentItem(); }

    void update_colormap()
    {
        update_data_controller();
        update_interpolation();
        update_gradient();
        m_custom_plot->replot();
    }

    void update_data_controller() { m_data_controller->setItem(colormap_item()->dataItem()); }

    //! Updates QCPColorMap's interpolation when corresponding property of ColorMapItem changed.

    void update_interpolation()
    {
        auto is_interpolated = colormap_item()->property<bool>(ColorMapItem::P_INTERPOLATION);
        m_color_map->setInterpolate(is_interpolated);
    }

    void update_gradient()
    {
        auto combo = colormap_item()->property<ComboProperty>(ColorMapItem::P_GRADIENT);
        m_color_map->setGradient(getGradient(combo.value()));
    }
};

ColorMapPlotController::ColorMapPlotController(QCustomPlot* custom_plot, QCPColorScale* color_scale)
    : p_impl(std::make_unique<ColorMapPlotControllerImpl>(this, custom_plot, color_scale))
{
}

void ColorMapPlotController::subscribe()
{
    auto on_property_change = [this](SessionItem*, std::string property_name) {
        if (property_name == ColorMapItem::P_INTERPOLATION)
            p_impl->update_interpolation();

        if (property_name == ColorMapItem::P_GRADIENT)
            p_impl->update_gradient();

        if (property_name == ColorMapItem::P_LINK)
            p_impl->update_data_controller();

        p_impl->m_custom_plot->replot();
    };
    setOnPropertyChange(on_property_change);

    p_impl->update_colormap();
}

void ColorMapPlotController::unsubscribe()
{
    p_impl->m_data_controller->setItem(nullptr);
}

ColorMapPlotController::~ColorMapPlotController() = default;
