// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/graphviewportitem.h"
#include "mvvm/standarditems/graphitem.h"
#include <algorithm>
#include <vector>

using namespace ModelView;

namespace {

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

GraphViewportItem::GraphViewportItem(const std::string& model_type) : ViewportItem(model_type)
{
    register_xy_axes();
    registerTag(TagInfo::universalTag(T_ITEMS, {Constants::GraphItemType}), /*set_default*/ true);
}

//! Returns the selected graph items.

std::vector<GraphItem*> GraphViewportItem::graphItems() const
{
    return items<GraphItem>(T_ITEMS);
}

//! Returns the selected graph items.

std::vector<GraphItem*> GraphViewportItem::visibleGraphItems() const
{
    std::vector<GraphItem*> all_items = items<GraphItem>(T_ITEMS);
    std::vector<GraphItem*> visible_items;
    std::copy_if(all_items.begin(), all_items.end(), std::back_inserter(visible_items),
                 [](const GraphItem* graph_item) {
                     return graph_item->property<bool>(GraphItem::P_DISPLAYED);
                 });
    return visible_items;
}

//! Set the graph selection.

void GraphViewportItem::setVisible(const std::vector<GraphItem*>& visible_graph_items)
{
    std::vector<GraphItem*> output;
    for (auto graph_item : items<GraphItem>(T_ITEMS)) {
        if (std::find(visible_graph_items.begin(), visible_graph_items.end(), graph_item)
            != visible_graph_items.end())
            graph_item->setProperty(GraphItem::P_DISPLAYED, true);
        else
            graph_item->setProperty(GraphItem::P_DISPLAYED, false);
    }
}

//! Reset the graph selection.

void GraphViewportItem::setAllVisible()
{
    for (auto graph_item : items<GraphItem>(T_ITEMS))
        graph_item->setProperty(GraphItem::P_DISPLAYED, true);
}

//! Returns lower, upper range on x-axis occupied by all data points of all graphs.

std::pair<double, double> GraphViewportItem::data_xaxis_range() const
{
    return get_min_max(visibleGraphItems(), [](GraphItem* graph) { return graph->binCenters(); });
}

//! Returns lower, upper range on y-axis occupied by all data points of all graphs.

std::pair<double, double> GraphViewportItem::data_yaxis_range() const
{
    return get_min_max(visibleGraphItems(), [](GraphItem* graph) { return graph->binValues(); });
}
