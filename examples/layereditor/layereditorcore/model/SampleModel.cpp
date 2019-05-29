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

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    std::unique_ptr<ModelView::ItemCatalogue> result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<MultiLayerItem>();
    result->registerItem<LayerItem>();
    return result;
}
} // namespace

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateItemCatalogue());

    auto multilayer = insertNewItem(Constants::MultiLayerType);
    auto layer = insertNewItem(Constants::LayerType, multilayer);

    auto assembly = insertNewItem(Constants::MultiLayerType, multilayer);
    layer = insertNewItem(Constants::LayerType, assembly);
    layer = insertNewItem(Constants::LayerType, assembly);

    layer = insertNewItem(Constants::LayerType, multilayer);
}
