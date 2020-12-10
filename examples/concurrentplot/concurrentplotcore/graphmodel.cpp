// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphmodel.h"
#include "toysimulation.h"
#include <QColor>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/widgets/widgetutils.h>

namespace
{

auto simulation_result(double amp_factor = 1.0)
{
    ToySimulation simulation(amp_factor);
    simulation.runSimulation();
    return simulation.simulationResult();
}

} // namespace

using namespace ModelView;

GraphModel::GraphModel() : SessionModel("GraphModel")
{
    init_model();
}

//! Sets new values for existing data item.

void GraphModel::set_data(const std::vector<double>& data)
{
    auto item = topItem<ContainerItem>()->item<Data1DItem>(ContainerItem::T_ITEMS);
    item->setValues(data);
}

//! Creates data container, Data1DItem, viewport and GraphItem.

void GraphModel::init_model()
{
    auto container = insertItem<ContainerItem>();
    container->setDisplayName("Data container");

    auto viewport = insertItem<GraphViewportItem>();
    viewport->setDisplayName("Graph container");

    add_graph(container, viewport);
}

//! Adds Graph1DItem with some random points.

void GraphModel::add_graph(ModelView::ContainerItem* container,
                           ModelView::GraphViewportItem* viewport)
{
    auto [xmin, xmax, points] = simulation_result(ModelView::Utils::RandDouble(0.5, 1.0));

    auto data = insertItem<Data1DItem>(container);
    data->setAxis<FixedBinAxisItem>(static_cast<int>(points.size()), xmin, xmax);
    data->setValues(points);

    auto graph = insertItem<GraphItem>(viewport);
    graph->setDataItem(data);
    graph->setNamedColor(ModelView::Utils::RandomNamedColor());
}
