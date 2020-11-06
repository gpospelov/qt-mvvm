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
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>

namespace
{
//! Returns Qt pen style from current ComboProperty index.
Qt::PenStyle getQtPenFromComboIndex(int index)
{
    // our ComboProperty for pens coincide with Qt definition
    return static_cast<Qt::PenStyle>(index);
}
} // namespace

using namespace ModelView;

struct GraphPlotController::GraphItemControllerImpl {
    GraphPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    QCPGraph* graph{nullptr};
    std::unique_ptr<Data1DPlotController> data_controller;

    GraphItemControllerImpl(GraphPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

    //! Setups controllers and updates graph properties.

    void init_graph()
    {
        graph = custom_plot->addGraph();
        data_controller = std::make_unique<Data1DPlotController>(graph);
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
        auto color = graph_item()->property<QColor>(GraphItem::P_COLOR);
        auto pencombo = graph_item()->property<ComboProperty>(GraphItem::P_PENSTYLE);
        auto penwidth = graph_item()->property<int>(GraphItem::P_PENWIDTH);

        QPen pen;
        pen.setColor(color);
        pen.setStyle(getQtPenFromComboIndex(pencombo.currentIndex()));
        pen.setWidth(penwidth);
        graph->setPen(pen);

        custom_plot->replot();
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
    auto on_property_change = [this](SessionItem* item, const std::string& property_name) {
        Q_UNUSED(item)
        if (property_name == GraphItem::P_COLOR || property_name == GraphItem::P_PENSTYLE
            || property_name == GraphItem::P_PENWIDTH)
            p_impl->update_graph_pen();

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
