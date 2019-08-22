// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "axesplotcontroller.h"
#include "qcustomplot.h"

using namespace ModelView;

struct AxesPlotController::AxesPlotControllerPrivate {
    QCustomPlot* m_customPlot{nullptr};
    GraphViewportItem* m_viewportItem{nullptr};
    AxesPlotControllerPrivate(QCustomPlot* plot) : m_customPlot(plot) {}
};

AxesPlotController::AxesPlotController(QCustomPlot* plot, QObject* parent)
    : ItemController(parent), p_impl(std::make_unique<AxesPlotControllerPrivate>(plot))
{
}

AxesPlotController::~AxesPlotController() = default;
