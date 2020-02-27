// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <vector>

using namespace ModelView;

namespace
{

const double failback_min = 0.0;
const double failback_max = 1.0;

//! Find min and max values along all data points in all graphs.
//! Function 'func' is used to run either through binCenters or binValues.

template <typename T> auto get_min_max(const std::vector<GraphItem*>& graphs, T func)
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
    registerTag(TagInfo::universalTag(T_ITEMS, {Constants::GraphItemType}), /*set_default*/ true);
}

std::vector<GraphItem*> GraphViewportItem::graphItems() const
{
    return items<GraphItem>(T_ITEMS);
}

//! Returns lower, upper range on x-axis occupied by all data points of all graphs.

std::pair<double, double> GraphViewportItem::data_xaxis_range() const
{
    return get_min_max(graphItems(), [](GraphItem* graph) { return graph->binCenters(); });
}

//! Returns lower, upper range on y-axis occupied by all data points of all graphs.

std::pair<double, double> GraphViewportItem::data_yaxis_range() const
{
    return get_min_max(graphItems(), [](GraphItem* graph) { return graph->binValues(); });
}
