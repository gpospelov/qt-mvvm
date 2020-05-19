// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "realdatamodel.h"
#include "datasetconvenience.h"
#include "datasetitem.h"

#include <mvvm/model/itemcatalogue.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

#include <algorithm>

using namespace ModelView;

namespace
{

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<DataGroupItem>();
    result->registerItem<DataCollectionItem>();
    return result;
}

} // namespace

RealDataModel::RealDataModel() : SessionModel("RealDataModel")
{
    setItemCatalogue(CreateItemCatalogue());
}

//! Create a new data node
DataCollectionItem* RealDataModel::insertDataNode()
{
    auto data_set_item = insertItem<DataCollectionItem>(rootItem());
    return data_set_item;
}

//! Check if a fitting data group already exists, if not create, then insert data
void RealDataModel::addDataToNode(DataCollectionItem* data_node, RealDataStruct data_struct)
{
    TypeUnit type_unit;
    type_unit.type = data_struct.type;
    type_unit.unit_pair =
        std::pair<std::string, std::string>(data_struct.axis_unit, data_struct.data_unit);

    auto group_item = hasTypeUnit(data_node, type_unit);
    if (!group_item) {
        group_item = addGroupItem(data_node);
        group_item->setTypeUnit(type_unit);
    }

    addDataToGroup(group_item, data_struct);
}

//! Insert the data into the group item
void RealDataModel::addDataToGroup(DataGroupItem* data_group, RealDataStruct& data_struct)
{
    if (data_struct.axis.empty()) {
        data_struct.axis.resize(data_struct.data.size());
        std::iota(data_struct.axis.begin(), data_struct.axis.end(), 0);
    }

    auto data = insertItem<Data1DItem>(
        data_group->item<ContainerItem>(DataGroupItem::P_DATA),
        {data_group->item<ContainerItem>(DataGroupItem::P_DATA)->defaultTag(), -1});
    data->setAxis(PointwiseAxisItem::create(data_struct.axis));
    data->setContent(data_struct.data);

    auto graph = insertItem<GraphItem>(data_group, {GraphViewportItem::T_ITEMS, -1});
    graph->setDisplayName(data_struct.name);

    graph->setDataItem(data);
}

//! Returns true on a h presence of a type
DataGroupItem* RealDataModel::hasTypeUnit(DataCollectionItem* data_node, TypeUnit& type_unit) const
{
    const std::string to_find_tag =
        type_unit.type + " (" + type_unit.unit_pair.first + "->" + type_unit.unit_pair.second + ")";
    return data_node->getDataGroup(to_find_tag);
}

//! Add a type unit sessionitem to the children
DataGroupItem* RealDataModel::addGroupItem(DataCollectionItem* data_node)
{
    auto item = insertItem<DataGroupItem>(data_node, {DataCollectionItem::data_group_tag, -1});
    return item;
}
