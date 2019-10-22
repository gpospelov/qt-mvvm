// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "data2dplotcontroller.h"
#include "qcustomplot.h"
#include "data2ditem.h"

using namespace ModelView;

struct Data2DPlotController::Data2DPlotControllerPrivate {
    QCPColorMap* color_map{nullptr};
    Data2DPlotControllerPrivate(QCPColorMap* color_map) : color_map(color_map) {
        if (!color_map)
            throw std::runtime_error("Uninitialised colormap in Data2DPlotController");
    }

};

Data2DPlotController::Data2DPlotController(QCPColorMap* color_map)
    : p_impl(std::make_unique<Data2DPlotControllerPrivate>(color_map))
{
}

Data2DPlotController::~Data2DPlotController() = default;

void Data2DPlotController::subscribe()
{
}

void Data2DPlotController::unsubscribe()
{
}
