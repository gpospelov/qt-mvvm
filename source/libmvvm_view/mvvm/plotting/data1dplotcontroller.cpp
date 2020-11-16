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
#include <stdexcept>

namespace
{
template <typename T> QVector<T> fromStdVector(const std::vector<T>& vec)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    return QVector<T>(vec.begin(), vec.end());
#else
    return QVector<T>::fromStdVector(vec);
#endif
}
} // namespace

using namespace ModelView;

struct Data1DPlotController::Data1DPlotControllerImpl {
    QCPGraph* m_graph{nullptr};
    Data1DPlotControllerImpl(QCPGraph* graph) : m_graph(graph)
    {
        if (!m_graph)
            throw std::runtime_error("Uninitialised graph in Data1DPlotController");
    }

    void updateGraphPointsFromItem(Data1DItem* item)
    {
        assert(item);
        m_graph->setData(fromStdVector<double>(item->binCenters()),
                         fromStdVector<double>(item->binValues()));
        m_graph->parentPlot()->replot();
    }

    void resetGraph()
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
    auto on_property_change = [this](SessionItem*, std::string property_name) {
        if (property_name == Data1DItem::P_VALUES)
            p_impl->updateGraphPointsFromItem(currentItem());
    };
    setOnPropertyChange(on_property_change);

    p_impl->updateGraphPointsFromItem(currentItem());
}

void Data1DPlotController::unsubscribe()
{
    p_impl->resetGraph();
}
