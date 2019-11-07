// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SampleModel.h"
#include "LayerItems.h"
#include <mvvm/model/itemcatalogue.h>

using namespace ModelView;

namespace
{
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<MultiLayerItem>();
    result->registerItem<LayerItem>();
    return result;
}
} // namespace

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateItemCatalogue());
    init_model();
}

//! Populats the model with some default content.

void SampleModel::init_model()
{
    auto multilayer = insertItem<MultiLayerItem>();
    insertItem<LayerItem>(multilayer);
    auto assembly = insertItem<MultiLayerItem>(multilayer);
    insertItem<LayerItem>(assembly);
    insertItem<LayerItem>(assembly);
    insertItem<LayerItem>(multilayer);
}
