// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "datasetitem.h"
#include "item_constants.h"

#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/containeritem.h>


#include <vector>

using namespace ModelView;

// ----------------------------------------------------------------
DataGroupItem::DataGroupItem() : GraphViewportItem(::Constants::DataGroupItemType)
{
    addProperty<ContainerItem>(P_DATA);
}

//! Set the type
void DataGroupItem::setTypeUnit(TypeUnit &type_unit)
{
    const std::string temp_name = type_unit.type+" ("+type_unit.unit_pair.first+"->"+type_unit.unit_pair.second+")";
    registerTag(TagInfo::universalTag(temp_name));
    setDisplayName(temp_name);
}

//! insert the data into the right places
void DataGroupItem::insertData(RealDataStruct& data_struct)
{
    if (data_struct.axis.empty()){
        data_struct.axis.resize(data_struct.data.size());
        std::iota(data_struct.axis.begin(), data_struct.axis.end(), 0);
    }

    auto data = new Data1DItem();
    data->setAxis(PointwiseAxisItem::create(data_struct.axis));
    data->setContent(data_struct.data);
    item<ContainerItem>(P_DATA)->insertItem(data, {item<ContainerItem>(P_DATA)->defaultTag(),-1});

    auto graph = new GraphItem();
    graph->setDisplayName(data_struct.name);
    insertItem(graph, {T_ITEMS, -1});

    graph->setDataItem(data);
}

// ----------------------------------------------------------------
DataCollectionItem::DataCollectionItem() : CompoundItem(::Constants::DataCollectionItemType)
{
    const std::string data_group_tag = "data_groups";
    registerTag(TagInfo::universalTag(data_group_tag));
}

//! Insert a data container into the system
void DataCollectionItem::insertData(RealDataStruct& data_struct)
{
    TypeUnit type_unit;
    type_unit.type = data_struct.type;
    type_unit.unit_pair = std::pair<std::string,std::string>(data_struct.axis_unit, data_struct.data_unit);

    auto group_item = hasTypeUnit(type_unit);
    if (!group_item){
        group_item = addTypeUnit(type_unit);
    }

    group_item->insertData(data_struct);
}

//! Returns true on a h presence of a type
DataGroupItem* DataCollectionItem::hasTypeUnit(TypeUnit& type_unit) const
{
    const std::string to_find_tag = type_unit.type+" ("+type_unit.unit_pair.first+"->"+type_unit.unit_pair.second+")";
    std::vector<SessionItem*> items = getItems(data_group_tag);
    auto found = std::find_if(items.begin(), items.end(), [&to_find_tag](const SessionItem* item){return item->isTag(to_find_tag);});

    if (found == items.end())
        return nullptr;
    else 
        return dynamic_cast<DataGroupItem*>(*found);
}

//! Add a type unit sessionitem to the children
DataGroupItem* DataCollectionItem::addTypeUnit(TypeUnit& type_unit)
{
    auto item = new DataGroupItem();
    item->setTypeUnit(type_unit);
    insertItem(item, {data_group_tag, -1});
    return item;
}
