// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "realdatamodel.h"
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

DataCollectionItem* RealDataModel::insertDataNode()
{
    auto data_set_item = insertItem<DataCollectionItem>(rootItem());
    return data_set_item;
}

void RealDataModel::addDataToNode(DataCollectionItem* data_set_item, RealDataStruct data_struct)
{
    data_set_item->insertData(data_struct);

    
}
