// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphitemcontroller.h"
#include "data1ditem.h"
#include "data1dplotcontroller.h"
#include "graphitem.h"
#include "itemmapper.h"
#include "qcustomplot.h"
#include <QVector>
#include <cassert>

using namespace ModelView;

struct GraphItemController::GraphItemControllerPrivate {
    GraphItemController* master{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    bool m_block_update{false};
    QCPGraph* m_graph{nullptr};
    std::unique_ptr<Data1DPlotController> data_controller;

    GraphItemControllerPrivate(GraphItemController* master, QCustomPlot* plot)
        : master(master), m_customPlot(plot)
    {
    }

    GraphItem* graph_item() { return master->currentItem(); }

    //! Removes graph from customPlot.
    void remove_graph()
    {
        if (!m_graph)
            return;

        data_controller.reset();
        m_customPlot->removePlottable(m_graph);
        m_graph = nullptr;
    }

    //! Creates graph on canvas and setups data controller.
    void create_graph()
    {
        m_graph = m_customPlot->addGraph();
        data_controller = std::make_unique<Data1DPlotController>(m_graph);
        data_controller->setItem(graph_item()->dataItem());
    }

    //! Updates graph pen from GraphItem.
    void update_graph_pen()
    {
        if (!m_graph)
            return;

        auto color = graph_item()->property(GraphItem::P_COLOR).value<QColor>();
        m_customPlot->graph()->setPen(QPen(color));
        m_customPlot->replot();
    }

    //! Creates graph for current GraphItem.
    void setup_graph() {
        remove_graph();
        create_graph();
        update_graph_pen();
    }
};

GraphItemController::GraphItemController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphItemControllerPrivate>(this, custom_plot))
{
}

void GraphItemController::subscribe()
{
    auto on_property_change = [this](SessionItem* item, std::string property_name) {
        Q_UNUSED(item)
        if (property_name == GraphItem::P_COLOR)
            p_impl->update_graph_pen();

        if (property_name == GraphItem::P_LINK)
            p_impl->setup_graph();
    };
    currentItem()->mapper()->setOnPropertyChange(on_property_change, this);

    p_impl->setup_graph();
}

void GraphItemController::unsubscribe()
{
    p_impl->remove_graph();
}

GraphItemController::~GraphItemController() = default;
