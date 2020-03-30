// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "jobitem.h"
#include "item_constants.h"
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

JobItem::JobItem() : ModelView::CompoundItem(::Constants::JobItemType)
{
    setup_graph(P_SLD_DATA, P_SLD_VIEWPORT);
    setup_graph(P_SPECULAR_DATA, P_SPECULAR_VIEWPORT);
}

Data1DItem *JobItem::sld_data() const
{
    return item<Data1DItem>(P_SLD_DATA);
}

GraphViewportItem *JobItem::sld_viewport() const
{
    return item<GraphViewportItem>(P_SLD_VIEWPORT);
}

Data1DItem *JobItem::specular_data() const
{
    return item<Data1DItem>(P_SLD_DATA);
}

GraphViewportItem *JobItem::specular_viewport() const
{
    return item<GraphViewportItem>(P_SLD_VIEWPORT);
}

//! Setup data, graph and viewport.

void JobItem::setup_graph(const std::string &data_tag, const std::string &viewport_tag)
{
    auto data = addProperty<Data1DItem>(data_tag);
    auto viewport = addProperty<GraphViewportItem>(viewport_tag);
    auto graph = std::make_unique<GraphItem>();
    graph->setDataItem(data);
    viewport->insertItem(graph.release(), {ViewportItem::T_ITEMS, 0});
}
