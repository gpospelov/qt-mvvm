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

using namespace ModelView;

namespace
{

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<DataSetItem>();
    return result;
}

} // namespace


RealDataModel::RealDataModel() : SessionModel("RealDataModel")
{
    setItemCatalogue(CreateItemCatalogue());
    insertItem<DataSetItem>();
}
