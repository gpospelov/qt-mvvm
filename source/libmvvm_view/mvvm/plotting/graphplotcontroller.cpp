// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/graphplotcontroller.h"
#include "mvvm/plotting/data1dplotcontroller.h"
#include "mvvm/plotting/pencontroller.h"
#include "mvvm/standarditems/data1ditem.h"
#include "mvvm/standarditems/graphitem.h"
#include "mvvm/standarditems/plottableitems.h"
#include <qcustomplot.h>

using namespace ModelView;

struct GraphPlotController::GraphItemControllerImpl {
    GraphPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPGraph* m_graph{nullptr};
    std::unique_ptr<Data1DPlotController> m_dataController;
    std::unique_ptr<PenController> m_penController;

    GraphItemControllerImpl(GraphPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot)
    {
    }

    //! Setups controllers and updates graph properties.

    void init_graph()
    {
        m_graph = m_customPlot->addGraph();
        m_dataController = std::make_unique<Data1DPlotController>(m_graph);
        m_penController = std::make_unique<PenController>(m_graph);

        update_data_controller();
        update_graph_pen();
        update_visible();
    }

    ~GraphItemControllerImpl()
    {
        if (m_graph)
            m_customPlot->removePlottable(m_graph);
    }

    GraphItem* graph_item() { return m_self->currentItem(); }

    void update_data_controller() { m_dataController->setItem(graph_item()->dataItem()); }

    //! Updates graph pen from GraphItem.

    void update_graph_pen() { m_penController->setItem(graph_item()->penItem()); }

    //! Update visible
    void update_visible()
    {
        m_graph->setVisible(graph_item()->property<bool>(GraphItem::P_DISPLAYED));
        m_customPlot->replot();
    }

    void reset_graph()
    {
        m_dataController->setItem(nullptr);
        m_penController->setItem(nullptr);
        m_customPlot->removePlottable(m_graph);
        m_graph = nullptr;
        m_customPlot->replot();
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
