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
#include <cmath>
#include <mvvm/model/modelutils.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/utils/numericutils.h>

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

void GraphModel::set_data(const std::vector<double>& data)
{
    auto item = data_container()->item<Data1DItem>(ContainerItem::T_ITEMS);
    item->setContent(data);
}

//! Returns viewport item containig graph items.

GraphViewportItem* GraphModel::viewport()
{
    return Utils::TopItem<GraphViewportItem>(this);
}

//! Returns container with data items.

ContainerItem* GraphModel::data_container()
{
    return Utils::TopItem<ContainerItem>(this);
}

void GraphModel::init_model()
{
    auto container = insertItem<ContainerItem>();
    container->setDisplayName("Data container");

    auto viewport = insertItem<GraphViewportItem>();
    viewport->setDisplayName("Graph container");
    add_graph();
}

//! Adds Graph1DItem with some random points.

void GraphModel::add_graph()
{
    auto [xmin, xmax, points] = simulation_result(ModelView::Utils::RandDouble(0.5, 1.0));

    auto data = insertItem<Data1DItem>(data_container());
    data->setAxis(FixedBinAxisItem::create(static_cast<int>(points.size()), xmin, xmax));
    data->setContent(points);

    auto graph = insertItem<GraphItem>(viewport());
    graph->setDataItem(data);
    auto rndm = []() -> int { return ModelView::Utils::RandInt(0, 255); };
    graph->setProperty(GraphItem::P_COLOR, QVariant::fromValue(QColor(rndm(), rndm(), rndm())));
}
