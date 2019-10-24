// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphplotcontroller.h"
#include "data1ditem.h"
#include "data1dplotcontroller.h"
#include "graphitem.h"
#include "itemmapper.h"
#include "qcustomplot.h"
#include <QVector>
#include <cassert>

using namespace ModelView;

struct GraphPlotController::GraphItemControllerPrivate {
    GraphPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    QCPGraph* graph{nullptr};
    std::unique_ptr<Data1DPlotController> data_controller;

    GraphItemControllerPrivate(GraphPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
        graph = custom_plot->addGraph();
        data_controller = std::make_unique<Data1DPlotController>(graph);
    }

    ~GraphItemControllerPrivate() { custom_plot->removePlottable(graph); }

    GraphItem* graph_item() { return master->currentItem(); }

    //! Updates data controller and graph properties.

    void update_graph()
    {
        update_data_controller();
        update_graph_pen();
    }

    void update_data_controller() { data_controller->setItem(graph_item()->dataItem()); }

    //! Updates graph pen from GraphItem.

    void update_graph_pen()
    {
        auto color = graph_item()->property(GraphItem::P_COLOR).value<QColor>();
        graph->setPen(QPen(color));
        custom_plot->replot();
    }
};

GraphPlotController::GraphPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphItemControllerPrivate>(this, custom_plot))
{
}

void GraphPlotController::subscribe()
{
    auto on_property_change = [this](SessionItem* item, std::string property_name) {
        Q_UNUSED(item)
        if (property_name == GraphItem::P_COLOR)
            p_impl->update_graph_pen();

        if (property_name == GraphItem::P_LINK)
            p_impl->update_data_controller();
    };
    currentItem()->mapper()->setOnPropertyChange(on_property_change, this);

    p_impl->update_graph();
}

void GraphPlotController::unsubscribe()
{
    p_impl->data_controller->setItem(nullptr);
}

GraphPlotController::~GraphPlotController() = default;
