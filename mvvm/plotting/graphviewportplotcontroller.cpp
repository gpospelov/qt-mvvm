// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphviewportplotcontroller.h"
#include "axisitems.h"
#include "axisplotcontrollers.h"
#include "graphitem.h"
#include "graphplotcontroller.h"
#include "graphviewportitem.h"

using namespace ModelView;

struct GraphViewportPlotController::GraphCollectionPlotControllerPrivate {
    GraphViewportPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    std::vector<std::unique_ptr<GraphPlotController>> graph_controllers;
    std::unique_ptr<AxisPlotController> xAxisController;
    std::unique_ptr<AxisPlotController> yAxisController;

    GraphCollectionPlotControllerPrivate(GraphViewportPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

    GraphViewportItem* viewport_item() { return master->currentItem(); }

    //! Setup controller components.
    void setup_components()
    {
        create_axis_controllers();
        create_graph_controllers();
    }

    //! Creates axes controllers.

    void create_axis_controllers()
    {
        auto viewport = viewport_item();

        xAxisController = std::make_unique<XAxisPlotController>(custom_plot);
        xAxisController->setItem(&viewport->item<ViewportAxisItem>(GraphViewportItem::P_XAXIS));

        yAxisController = std::make_unique<YAxisPlotController>(custom_plot);
        yAxisController->setItem(&viewport->item<ViewportAxisItem>(GraphViewportItem::P_YAXIS));
    }

    //! Run through all GraphItem's and create graph controllers for QCustomPlot.

    void create_graph_controllers()
    {
        auto viewport = viewport_item();
        for (auto graph_item : viewport->graphItems()) {
            auto controller = std::make_unique<GraphPlotController>(custom_plot);
            controller->setItem(graph_item);
            graph_controllers.emplace_back(std::move(controller));
        }
        viewport->update_viewport();
    }
};

GraphViewportPlotController::GraphViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphCollectionPlotControllerPrivate>(this, custom_plot))
{
}

void GraphViewportPlotController::subscribe()
{
    p_impl->setup_components();
}

GraphViewportPlotController::~GraphViewportPlotController() = default;
