// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphviewportplotcontroller.h"
#include "graphviewportitem.h"
#include "graphplotcontroller.h"
#include "graphitem.h"

using namespace ModelView;

struct GraphViewportPlotController::GraphCollectionPlotControllerPrivate {
    GraphViewportPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    std::vector<std::unique_ptr<GraphPlotController>> graph_controllers;

    GraphCollectionPlotControllerPrivate(GraphViewportPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

    GraphViewportItem* viewport_item() { return master->currentItem(); }

    //! Run through all GraphItem and populate
    void setup_graphs() {
        auto viewport = viewport_item();
        for (auto graph_item : viewport->items<GraphItem>(GraphViewportItem::T_GRAPHS)) {
            auto controller = std::make_unique<GraphPlotController>(custom_plot);
            controller->setItem(graph_item);
        }
    }
};

GraphViewportPlotController::GraphViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphCollectionPlotControllerPrivate>(this, custom_plot))
{
}

void GraphViewportPlotController::subscribe()
{
    p_impl->setup_graphs();
}

GraphViewportPlotController::~GraphViewportPlotController() = default;
