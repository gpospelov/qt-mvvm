// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphcollectionplotcontroller.h"
#include "graphviewportitem.h"

using namespace ModelView;

struct GraphCollectionPlotController::GraphCollectionPlotControllerPrivate {
    GraphCollectionPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};

    GraphCollectionPlotControllerPrivate(GraphCollectionPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

};

GraphCollectionPlotController::GraphCollectionPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphCollectionPlotControllerPrivate>(this, custom_plot))
{
}

void GraphCollectionPlotController::subscribe()
{
}

GraphCollectionPlotController::~GraphCollectionPlotController() = default;
