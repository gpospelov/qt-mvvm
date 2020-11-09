// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "qcustomplot.h"
#include <mvvm/model/comboproperty.h>
#include <mvvm/plotting/data1dplotcontroller.h>
#include <mvvm/plotting/graphplotcontroller.h>
#include <mvvm/plotting/pencontroller.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/plottableitems.h>

using namespace ModelView;

struct GraphPlotController::GraphItemControllerImpl {
    GraphPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    QCPGraph* graph{nullptr};
    std::unique_ptr<Data1DPlotController> data_controller;
    std::unique_ptr<PenController> pen_controller;

    GraphItemControllerImpl(GraphPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

    //! Setups controllers and updates graph properties.

    void init_graph()
    {
        graph = custom_plot->addGraph();
        data_controller = std::make_unique<Data1DPlotController>(graph);
        pen_controller = std::make_unique<PenController>(graph);

        update_data_controller();
        update_graph_pen();
        update_visible();
    }

    ~GraphItemControllerImpl()
    {
        if (graph)
            custom_plot->removePlottable(graph);
    }

    GraphItem* graph_item() { return master->currentItem(); }

    void update_data_controller() { data_controller->setItem(graph_item()->dataItem()); }

    //! Updates graph pen from GraphItem.

    void update_graph_pen()
    {
        pen_controller->setItem(graph_item()->item<PenItem>(GraphItem::P_PEN));
    }

    //! Update visible
    void update_visible()
    {
        graph->setVisible(graph_item()->property<bool>(GraphItem::P_DISPLAYED));
        custom_plot->replot();
    }

    void reset_graph()
    {
        data_controller->setItem(nullptr);
        pen_controller->setItem(nullptr);
        custom_plot->removePlottable(graph);
        graph = nullptr;
        custom_plot->replot();
    }
};

GraphPlotController::GraphPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphItemControllerImpl>(this, custom_plot))
{
}

void GraphPlotController::subscribe()
{
    auto on_property_change = [this](SessionItem*, const std::string& property_name) {
        if (property_name == GraphItem::P_LINK)
            p_impl->update_data_controller();

        if (property_name == GraphItem::P_DISPLAYED)
            p_impl->update_visible();
    };
    setOnPropertyChange(on_property_change);

    p_impl->init_graph();
}

void GraphPlotController::unsubscribe()
{
    p_impl->reset_graph();
}

GraphPlotController::~GraphPlotController() = default;
