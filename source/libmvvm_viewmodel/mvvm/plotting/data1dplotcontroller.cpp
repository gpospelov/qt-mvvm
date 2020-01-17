// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "qcustomplot.h"
#include <mvvm/plotting/data1dplotcontroller.h>
#include <mvvm/standarditems/data1ditem.h>

namespace {
template<typename T>
QVector<T> fromStdVector(const std::vector<T>& vec)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    return QVector<T>(vec.begin(), vec.end());
#else
    return QVector<T>>::fromStdVector(vec);
#endif
}
}

using namespace ModelView;

struct Data1DPlotController::Data1DPlotControllerImpl {
    QCPGraph* m_graph{nullptr};
    Data1DPlotControllerImpl(QCPGraph* graph) : m_graph(graph)
    {
        if (!m_graph)
            throw std::runtime_error("Uninitialised graph in Data1DPlotController");
    }

    void update_graph_points(Data1DPlotController* controller)
    {
        auto data_item = controller->currentItem();
        if (data_item) {
            m_graph->setData(fromStdVector<double>(data_item->binCenters()),
                             fromStdVector<double>(data_item->binValues()));
            m_graph->parentPlot()->replot();
        }
    }

    void reset_graph()
    {
        m_graph->setData(QVector<double>{}, QVector<double>{});
        m_graph->parentPlot()->replot();
    }
};

Data1DPlotController::Data1DPlotController(QCPGraph* graph)
    : p_impl(std::make_unique<Data1DPlotControllerImpl>(graph))
{
}

Data1DPlotController::~Data1DPlotController() = default;

void Data1DPlotController::subscribe()
{
    auto on_data_change = [this](SessionItem*, int) { p_impl->update_graph_points(this); };
    currentItem()->mapper()->setOnDataChange(on_data_change, this);

    p_impl->update_graph_points(this);
}

void Data1DPlotController::unsubscribe()
{
    p_impl->reset_graph();
}
