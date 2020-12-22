// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/data1dplotcontroller.h"
#include "mvvm/standarditems/data1ditem.h"
#include <qcustomplot.h>
#include <stdexcept>

namespace {
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
    QCPErrorBars* m_errorBars{nullptr};

    Data1DPlotControllerImpl(QCPGraph* graph) : m_graph(graph)
    {
        if (!m_graph)
            throw std::runtime_error("Uninitialised graph in Data1DPlotController");
    }

    void initGraphFromItem(Data1DItem* item)
    {
        assert(item);
        updateGraphPointsFromItem(item);
        updateErrorBarsFromItem(item);
    }

    void updateGraphPointsFromItem(Data1DItem* item)
    {
        m_graph->setData(fromStdVector<double>(item->binCenters()),
                         fromStdVector<double>(item->binValues()));
        customPlot()->replot();
    }

    void updateErrorBarsFromItem(Data1DItem* item)
    {
        auto errors = item->binErrors();
        if (errors.empty()) {
            resetErrorBars();
            return;
        }

        if (!m_errorBars)
            m_errorBars = new QCPErrorBars(customPlot()->xAxis, customPlot()->yAxis);

        m_errorBars->setData(fromStdVector<double>(errors));
        m_errorBars->setDataPlottable(m_graph);
    }

    void resetGraph()
    {
        m_graph->setData(QVector<double>{}, QVector<double>{});
        customPlot()->replot();
    }

    void resetErrorBars()
    {
        delete m_errorBars;
        m_errorBars = nullptr;
    }

    QCustomPlot* customPlot()
    {
        assert(m_graph);
        return m_graph->parentPlot();
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
        if (property_name == Data1DItem::P_ERRORS)
            p_impl->updateErrorBarsFromItem(currentItem());
    };
    setOnPropertyChange(on_property_change);

    p_impl->initGraphFromItem(currentItem());
}

void Data1DPlotController::unsubscribe()
{
    p_impl->resetGraph();
}
