// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colorscaleplotcontroller.h"
#include "qcustomplot.h"
#include "axisitems.h"

using namespace ModelView;

struct ColorScalePlotController::ColorScalePlotControllerPrivate {

    ColorScalePlotController* controller{nullptr};
    QCPColorScale* axis{nullptr};

    ColorScalePlotControllerPrivate(ColorScalePlotController* controller, QCPColorScale* axis)
        : controller(controller), axis(axis)
    {
        if (!axis)
            throw std::runtime_error("ColorScalePlotController: axis is not initialized.");
    }
};

ColorScalePlotController::ColorScalePlotController(QCPColorScale* color_scale)
    : p_impl(std::make_unique<ColorScalePlotControllerPrivate>(this, color_scale))

{
}

ColorScalePlotController::~ColorScalePlotController() = default;

void ColorScalePlotController::subscribe() {}
