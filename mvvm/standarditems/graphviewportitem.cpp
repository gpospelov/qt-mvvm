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

GraphViewportItem::GraphViewportItem() : ViewportItem(Constants::GraphViewportItemType)
{
    register_xy_axes();
    registerTag(TagInfo::universalTag(T_GRAPHS, {Constants::GraphItemType}), /*set_default*/ true);
}

std::vector<GraphItem*> GraphViewportItem::graphItems() const
{
    return items<GraphItem>(T_GRAPHS);
}

//! Returns lower, upper range on x-axis occupied by all data points of all graphs.

std::pair<double, double> GraphViewportItem::data_xrange() const
{
    return get_min_max(items<GraphItem>(T_GRAPHS), [](GraphItem* graph) { return graph->binCenters(); });
}

//! Returns lower, upper range on y-axis occupied by all data points of all graphs.

std::pair<double, double> GraphViewportItem::data_yrange() const
{
    return get_min_max(items<GraphItem>(T_GRAPHS), [](GraphItem* graph) { return graph->binValues(); });
}
