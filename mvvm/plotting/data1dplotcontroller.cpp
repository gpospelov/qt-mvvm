// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "data1dplotcontroller.h"
#include "qcustomplot.h"
#include "data1ditem.h"

using namespace ModelView;

struct Data1DPlotController::Data1DPlotControllerPrivate {
    QCPGraph* m_graph{nullptr};
    Data1DPlotControllerPrivate(QCPGraph* graph) : m_graph(graph) {

    }

    void update_graph_points(Data1DPlotController* controller) {
        if(!m_graph)
                return;
        auto graph_item = controller->currentItem();
        m_graph->setData(QVector<double>::fromStdVector(graph_item->binCenters()),
                       QVector<double>::fromStdVector(graph_item->binValues()));

    }

    void reset_graph() {
        if(!m_graph)
                return;
        m_graph->setData(QVector<double>{}, QVector<double>{});
    }

};

Data1DPlotController::Data1DPlotController(QCPGraph* graph)
    : p_impl(std::make_unique<Data1DPlotControllerPrivate>(graph))
{
}

Data1DPlotController::~Data1DPlotController() = default;

void Data1DPlotController::subscribe()
{
    auto on_data_change = [this](SessionItem*, int) {
        p_impl->update_graph_points(this);
    };
    currentItem()->mapper()->setOnDataChange(on_data_change, this);

    p_impl->update_graph_points(this);
}

void Data1DPlotController::unsubscribe()
{
    p_impl->reset_graph();
}
