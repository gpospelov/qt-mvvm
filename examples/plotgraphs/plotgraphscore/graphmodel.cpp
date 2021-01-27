// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphmodel.h"
#include "mvvm/interfaces/undostackinterface.h"
#include "mvvm/standarditems/standarditemincludes.h"
#include "mvvm/utils/numericutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QColor>
#include <cmath>
#include <stdexcept>

namespace {

constexpr double pi = 3.14159265358979323846;
constexpr int npoints = 400;
constexpr double xmin = 0.0;
constexpr double xmax = 5.0;
constexpr double dx = (xmax - xmin) / npoints;

std::vector<double> bin_values(double amp_factor = 1.0)
{
    std::vector<double> result;
    for (int i = 0; i < npoints; ++i) {
        double x = xmin + i * dx;
        double value = amp_factor * 10.0 * std::sin(2.0 * pi * 2 * x)
                       + amp_factor * 5.0 * std::sin(2 * pi * 2.25 * x);
        result.push_back(value);
    }
    return result;
}
} // namespace

using namespace ModelView;

namespace PlotGraphs {

GraphModel::GraphModel() : SessionModel("GraphModel")
{
    populateModel();
}

//! Adds Graph1DItem with some random points.

void GraphModel::addGraph()
{
    if (undoStack())
        undoStack()->beginMacro("addGraph");

    auto data = insertItem<Data1DItem>(dataContainer());
    data->setAxis<FixedBinAxisItem>(npoints, xmin, xmax);
    data->setValues(bin_values(ModelView::Utils::RandDouble(0.5, 1.0)));

    auto graph = insertItem<GraphItem>(viewport());
    graph->setDataItem(data);
    graph->setNamedColor(ModelView::Utils::RandomNamedColor());

    if (undoStack())
        undoStack()->endMacro();
}

//! Remove last graph and data item.

void GraphModel::removeGraph()
{
    if (undoStack())
        undoStack()->beginMacro("removeGraph");

    const int graph_count = viewport()->itemCount(ViewportItem::T_ITEMS);
    const int data_count = dataContainer()->itemCount(ContainerItem::T_ITEMS);

    if (graph_count != data_count)
        throw std::runtime_error("Number of graphs do not much number of data items.");

    if (graph_count)
        removeItem(viewport(), {"", graph_count - 1});

    if (data_count)
        removeItem(dataContainer(), {"", data_count - 1});

    if (undoStack())
        undoStack()->endMacro();
}

//! Put random noise to graph.

void GraphModel::randomizeGraphs()
{
    for (auto item : dataContainer()->items<Data1DItem>(ContainerItem::T_ITEMS)) {
        auto values = item->binValues();
        std::transform(std::begin(values), std::end(values), std::begin(values),
                       [](auto x) { return x * ModelView::Utils::RandDouble(0.8, 1.2); });
        item->setValues(values);
    }
}

void GraphModel::undo()
{
    if (undoStack())
        undoStack()->undo();
}

void GraphModel::redo()
{
    if (undoStack())
        undoStack()->redo();
}

//! Returns viewport item containig graph items.

GraphViewportItem* GraphModel::viewport()
{
    return topItem<GraphViewportItem>();
}

//! Returns container with data items.

ContainerItem* GraphModel::dataContainer()
{
    return topItem<ContainerItem>();
}

void GraphModel::populateModel()
{
    auto container = insertItem<ContainerItem>();
    container->setDisplayName("Data container");

    auto viewport = insertItem<GraphViewportItem>();
    viewport->setDisplayName("Graph container");

    addGraph();
    setUndoRedoEnabled(true);
}

} // namespace PlotGraphs
