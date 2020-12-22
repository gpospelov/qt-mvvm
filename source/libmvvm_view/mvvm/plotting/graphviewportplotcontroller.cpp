// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/graphviewportplotcontroller.h"
#include "mvvm/plotting/graphplotcontroller.h"
#include "mvvm/plotting/viewportaxisplotcontroller.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/graphitem.h"
#include "mvvm/standarditems/graphviewportitem.h"
#include <qcustomplot.h>
#include <list>
#include <stdexcept>

using namespace ModelView;

struct GraphViewportPlotController::GraphViewportPlotControllerImpl {
    GraphViewportPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    std::list<std::unique_ptr<GraphPlotController>> graph_controllers;
    std::unique_ptr<ViewportAxisPlotController> xAxisController;
    std::unique_ptr<ViewportAxisPlotController> yAxisController;

    GraphViewportPlotControllerImpl(GraphViewportPlotController* master, QCustomPlot* plot)
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

        xAxisController = std::make_unique<ViewportAxisPlotController>(custom_plot->xAxis);
        xAxisController->setItem(viewport->xAxis());

        yAxisController = std::make_unique<ViewportAxisPlotController>(custom_plot->yAxis);
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
        viewport->setViewportToContent();
    }

    //! Adds controller for item.
    void add_controller_for_item(SessionItem* parent, const TagRow& tagrow)
    {
        auto added_child = dynamic_cast<GraphItem*>(parent->getItem(tagrow.tag, tagrow.row));

        for (auto& controller : graph_controllers)
            if (controller->currentItem() == added_child)
                throw std::runtime_error("Attempt to create second controller");

        auto controller = std::make_unique<GraphPlotController>(custom_plot);
        controller->setItem(added_child);
        graph_controllers.push_back(std::move(controller));
        custom_plot->replot();
    }

    //! Remove GraphPlotController corresponding to GraphItem.

    void remove_controller_for_item(SessionItem* parent, const TagRow& tagrow)
    {
        auto child_about_to_be_removed = parent->getItem(tagrow.tag, tagrow.row);
        auto if_func = [&](const std::unique_ptr<GraphPlotController>& cntrl) -> bool {
            return cntrl->currentItem() == child_about_to_be_removed;
        };
        graph_controllers.remove_if(if_func);
        custom_plot->replot();
    }
};

GraphViewportPlotController::GraphViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphViewportPlotControllerImpl>(this, custom_plot))
{
}

void GraphViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](SessionItem* parent, TagRow tagrow) {
        p_impl->add_controller_for_item(parent, tagrow);
    };
    setOnItemInserted(on_item_inserted);

    auto on_about_to_remove_item = [this](SessionItem* parent, TagRow tagrow) {
        p_impl->remove_controller_for_item(parent, tagrow);
    };
    setOnAboutToRemoveItem(on_about_to_remove_item);

    p_impl->setup_components();
}

GraphViewportPlotController::~GraphViewportPlotController() = default;
