// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colorscaleplotcontroller.h"
#include "axisitems.h"
#include "qcustomplot.h"
#include "viewportaxisplotcontroller.h"

using namespace ModelView;

struct ColorScalePlotController::ColorScalePlotControllerPrivate {

    ColorScalePlotController* controller{nullptr};
    QCPColorScale* color_scale{nullptr};
    QCPLayoutGrid* layout_grid{new QCPLayoutGrid};
    std::unique_ptr<ViewportAxisPlotController> axisController;
    QCPMarginGroup* margin_group{nullptr};

    ColorScalePlotControllerPrivate(ColorScalePlotController* controller,
                                    QCPColorScale* color_scale)
        : controller(controller), color_scale(color_scale)
    {
        if (!color_scale)
            throw std::runtime_error("ColorScalePlotController: axis is not initialized.");

        axisController = std::make_unique<ViewportAxisPlotController>(color_scale->axis());

        show_colorscale();
        setup_margins();
    }

    void setup_components() { axisController->setItem(controller->currentItem()); }

    void show_colorscale()
    {
        if (!layout_grid->hasElement(0, 0))
            layout_grid->addElement(0, 0, color_scale);

        layout_grid->setVisible(true);
        customPlot()->plotLayout()->addElement(0, 1, layout_grid);
    }

    void hide_colorscale()
    {
        layout_grid->setVisible(false);
        customPlot()->plotLayout()->take(layout_grid);
        customPlot()->plotLayout()->simplify();
    }

    //! Setup margins of color scale to match top/bottom margins of axis rectangle.

    void setup_margins()
    {
        if (margin_group)
            return;
        margin_group = new QCPMarginGroup(customPlot());
        customPlot()->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, margin_group);
        color_scale->setMarginGroup(QCP::msBottom | QCP::msTop, margin_group);
    }

    QCustomPlot* customPlot() { return color_scale->parentPlot(); }
};

ColorScalePlotController::ColorScalePlotController(QCPColorScale* color_scale)
    : p_impl(std::make_unique<ColorScalePlotControllerPrivate>(this, color_scale))

{
}

ColorScalePlotController::~ColorScalePlotController() = default;

void ColorScalePlotController::subscribe()
{
    p_impl->setup_components();
}
