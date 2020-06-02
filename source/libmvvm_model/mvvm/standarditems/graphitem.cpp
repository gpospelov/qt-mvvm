// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/linkeditem.h>
#include <mvvm/standarditems/plottableitems.h>

using namespace ModelView;

GraphItem::GraphItem(const std::string& model_type) : CompoundItem(model_type)
{
    addProperty<LinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<TextItem>(P_GRAPH_TITLE)->setDisplayName("Graph title");
    addProperty(P_COLOR, QColor(Qt::black))->setDisplayName("Color");
}

//! Sets link to the data item.

void GraphItem::setDataItem(const Data1DItem* data_item)
{
    item<LinkedItem>(P_LINK)->setLink(data_item);
}

//! Returns data item linked to the given GraphItem.

Data1DItem* GraphItem::dataItem() const
{
    return item<LinkedItem>(P_LINK)->get<Data1DItem>();
}

std::vector<double> GraphItem::binCenters() const
{
    return dataItem() ? dataItem()->binCenters() : std::vector<double>();
}

std::vector<double> GraphItem::binValues() const
{
    return dataItem() ? dataItem()->binValues() : std::vector<double>();
}
