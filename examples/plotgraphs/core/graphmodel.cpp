// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphmodel.h"
#include "mvvm_types.h"
#include "data1ditem.h"
#include "graphitem.h"
#include "graphviewportitem.h"
#include "modelutils.h"
#include "containeritem.h"
#include "numericutils.h"
#include <cmath>
#include <QColor>

namespace {

constexpr double pi = 3.14159265358979323846;
constexpr int npoints = 400;
constexpr double xmin = 0.0;
constexpr double xmax = 5.0;
constexpr double dx = (xmax-xmin)/npoints;

std::vector<double> bin_values(double amp_factor = 1.0) {
    std::vector<double> result;
    for(int i=0; i<npoints; ++i) {
        double x = xmin + i * dx;
        double value = amp_factor*10.0*std::sin(2.0*pi*2*x) + amp_factor*5.0*std::sin(2*pi*2.25*x);
        result.push_back(value);
    }
    return result;
}


}

using namespace ModelView;

GraphModel::GraphModel() : SessionModel("GraphModel")
{
    init_model();
}

//! Adds Graph1DItem with some random points.

void GraphModel::add_graph()
{
    auto data = dynamic_cast<Data1DItem*>(insertNewItem(Constants::Data1DItemType, data_container()));
    data->setFixedBinAxis(npoints, xmin, xmax);
    data->setContent(bin_values(ModelView::Utils::RandDouble(0.5, 1.0)));

    auto graph = dynamic_cast<GraphItem*>(insertNewItem(Constants::GraphItemType, viewport()));
    graph->setDataItem(data);
    auto rndm = []() -> int { return ModelView::Utils::RandInt(0, 255); };
    graph->setProperty(GraphItem::P_COLOR, QVariant::fromValue(QColor(rndm(), rndm(), rndm())));
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
    auto container = insertNewItem(Constants::ContainerType);
    container->setDisplayName("Data container");

    auto viewport = insertNewItem(Constants::GraphViewportItemType);
    viewport->setDisplayName("Graph container");
    add_graph();
}
