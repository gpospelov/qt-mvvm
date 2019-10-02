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
#include <qcustomplot.h>
#include <list>

using namespace ModelView;

struct GraphViewportPlotController::GraphViewportPlotControllerPrivate {
    GraphViewportPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    std::list<std::unique_ptr<GraphPlotController>> graph_controllers;
    std::unique_ptr<AxisPlotController> xAxisController;
    std::unique_ptr<AxisPlotController> yAxisController;

    GraphViewportPlotControllerPrivate(GraphViewportPlotController* master, QCustomPlot* plot)
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
        xAxisController->setItem(viewport->xAxis());

        yAxisController = std::make_unique<YAxisPlotController>(custom_plot);
        yAxisController->setItem(viewport->yAxis());
    }

    //! Run through all GraphItem's and create graph controllers for QCustomPlot.

    void create_graph_controllers()
    {
        graph_controllers.clear();
        auto viewport = viewport_item();
        for (auto graph_item : viewport->graphItems()) {
            auto controller = std::make_unique<GraphPlotController>(custom_plot);
            controller->setItem(graph_item);
            graph_controllers.push_back(std::move(controller));
        }
        viewport->update_viewport();
    }

    //! Adds controller for item.
    void add_controller_for_item(SessionItem* parent, const std::string& tag, int row)
    {
        auto added_child = dynamic_cast<GraphItem*>(parent->getItem(tag, row));

        for (auto& controller : graph_controllers)
            if (controller->currentItem() == added_child)
                throw std::runtime_error("Attempt to create second controller");

        auto controller = std::make_unique<GraphPlotController>(custom_plot);
        controller->setItem(added_child);
        graph_controllers.push_back(std::move(controller));
        custom_plot->replot();
    }

    //! Remove GraphPlotController corresponding to GraphItem.

    void remove_controller_for_item(SessionItem* parent, const std::string& tag, int row)
    {
        auto child_about_to_be_removed = parent->getItem(tag, row);
        auto if_func = [&](const std::unique_ptr<GraphPlotController>& cntrl) -> bool {
            return cntrl->currentItem() == child_about_to_be_removed;
        };
        graph_controllers.remove_if(if_func);
        custom_plot->replot();
    }
};

GraphViewportPlotController::GraphViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphViewportPlotControllerPrivate>(this, custom_plot))
{
}

void GraphViewportPlotController::subscribe()
{
    auto on_row_inserted = [this](SessionItem* parent, std::string tag, int row) {
        p_impl->add_controller_for_item(parent, tag, row);
    };
    currentItem()->mapper()->setOnRowInserted(on_row_inserted, this);

    auto on_row_about_to_be_removed = [this](SessionItem* parent, std::string tag, int row) {
        p_impl->remove_controller_for_item(parent, tag, row);
    };
    currentItem()->mapper()->setOnRowAboutToBeRemoved(on_row_about_to_be_removed, this);

    p_impl->setup_components();
}

GraphViewportPlotController::~GraphViewportPlotController() = default;
