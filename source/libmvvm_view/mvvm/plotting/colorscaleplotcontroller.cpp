// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/colorscaleplotcontroller.h"
#include "mvvm/plotting/viewportaxisplotcontroller.h"
#include "mvvm/standarditems/axisitems.h"
#include <qcustomplot.h>
#include <memory>
#include <stdexcept>
#include <string>

using namespace ModelView;

struct ColorScalePlotController::ColorScalePlotControllerImpl {

    ColorScalePlotController* m_controller{nullptr};
    QCPColorScale* m_color_scale{nullptr};
    QCPLayoutGrid* m_layout_grid{new QCPLayoutGrid};
    std::unique_ptr<ViewportAxisPlotController> m_axisController;
    QCPMarginGroup* m_margin_group{nullptr};

    ColorScalePlotControllerImpl(ColorScalePlotController* controller, QCPColorScale* color_scale)
        : m_controller(controller), m_color_scale(color_scale)
    {
        if (!color_scale)
            throw std::runtime_error("ColorScalePlotController: axis is not initialized.");

        m_axisController = std::make_unique<ViewportAxisPlotController>(color_scale->axis());
    }

    void setup_components()
    {
        m_axisController->setItem(m_controller->currentItem());
        update_log_scale();
        show_colorscale();
        setup_margins();
    }

    //! Updates color scale for log10.

    void update_log_scale()
    {
        const bool is_log = m_controller->currentItem()->is_in_log();
        m_color_scale->setDataScaleType(is_log ? QCPAxis::stLogarithmic : QCPAxis::stLinear);
    }

    void show_colorscale()
    {
        if (!m_layout_grid->hasElement(0, 0))
            m_layout_grid->addElement(0, 0, m_color_scale);

        m_layout_grid->setVisible(true);
        customPlot()->plotLayout()->addElement(0, 1, m_layout_grid);
    }

    void hide_colorscale()
    {
        m_layout_grid->setVisible(false);
        customPlot()->plotLayout()->take(m_layout_grid);
        customPlot()->plotLayout()->simplify();
    }

    //! Setup margins of color scale to match top/bottom margins of axis rectangle.

    void setup_margins()
    {
        if (m_margin_group)
            return;

        if (!customPlot()->axisRect())
            return;
        m_margin_group = new QCPMarginGroup(customPlot());
        customPlot()->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, m_margin_group);
        m_color_scale->setMarginGroup(QCP::msBottom | QCP::msTop, m_margin_group);
    }

    QCustomPlot* customPlot() { return m_color_scale->parentPlot(); }
};

ColorScalePlotController::ColorScalePlotController(QCPColorScale* color_scale)
    : p_impl(std::make_unique<ColorScalePlotControllerImpl>(this, color_scale))

{
}

ColorScalePlotController::~ColorScalePlotController() = default;

void ColorScalePlotController::subscribe()
{
    auto on_property_change = [this](SessionItem*, std::string property_name) {
        if (property_name == ViewportAxisItem::P_IS_LOG)
            p_impl->update_log_scale();
    };
    setOnPropertyChange(on_property_change);

    p_impl->setup_components();
}
