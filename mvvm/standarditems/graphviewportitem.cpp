// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphviewportitem.h"
#include "axisitems.h"
#include "graphitem.h"
#include <algorithm>
#include <vector>

using namespace ModelView;

namespace
{

const double failback_min = 0.0;
const double failback_max = 1.0;
const double ymax_factor = 1.1;

//! Find min and max values along all data points in all graphs.
//! Function 'func' is used to run either through binCenters or binValues.

template <typename T> auto get_min_max(std::vector<GraphItem*> graphs, T func)
{
    std::vector<double> values;
    for (auto graph : graphs) {
        const auto array = func(graph);
        std::copy(std::begin(array), std::end(array), std::back_inserter(values));
    }

    auto [xmin, xmax] = std::minmax_element(std::begin(values), std::end(values));
    return xmin != xmax ? std::make_pair(*xmin, *xmax) : std::make_pair(failback_min, failback_max);
}

} // namespace

GraphViewportItem::GraphViewportItem() : CompoundItem(Constants::GraphViewportItemType)
{
    addProperty<ViewportAxisItem>(P_XAXIS)->setDisplayName("X axis");
    addProperty<ViewportAxisItem>(P_YAXIS)->setDisplayName("Y axis");
    registerTag(TagInfo::universalTag(T_GRAPHS, {Constants::GraphItemType}), /*set_default*/ true);
}

//! Updates viewport axes depending on data points.

void GraphViewportItem::update_viewport()
{
    update_xaxis_range();
    update_yaxis_range();
}

//! Update x-axis range.

void GraphViewportItem::update_xaxis_range()
{
    const auto [xmin, xmax] = get_min_max(items<GraphItem>(T_GRAPHS),
                                          [](GraphItem* graph) { return graph->binCenters(); });
    item<ViewportAxisItem>(P_XAXIS).setProperty(ViewportAxisItem::P_MIN, xmin);
    item<ViewportAxisItem>(P_XAXIS).setProperty(ViewportAxisItem::P_MAX, xmax);
}

//! Update y-axis range.

void GraphViewportItem::update_yaxis_range()
{
    const auto [ymin, ymax] = get_min_max(items<GraphItem>(T_GRAPHS),
                                          [](GraphItem* graph) { return graph->binValues(); });
    item<ViewportAxisItem>(P_YAXIS).setProperty(ViewportAxisItem::P_MIN, ymin);
    item<ViewportAxisItem>(P_YAXIS).setProperty(ViewportAxisItem::P_MAX, ymax * ymax_factor);
}
