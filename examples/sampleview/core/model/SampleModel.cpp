// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "SampleModel.h"
#include "LayerItems.h"
#include "item_constants.h"
#include "itemcatalogue.h"

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
    auto layer = insertItem<LayerItem>(multilayer);
    auto assembly = insertItem<MultiLayerItem>(multilayer);
    layer = insertItem<LayerItem>(assembly);
    layer = insertItem<LayerItem>(assembly);
    layer = insertItem<LayerItem>(multilayer);
}
