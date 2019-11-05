// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "SampleModel.h"
#include "InterferenceFunctionItem.h"
#include "LayerItems.h"
#include "ParticleLayoutItem.h"
#include "item_constants.h"
#include <mvvm/model/itemcatalogue.h>

using namespace ModelView;

namespace
{
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<MultiLayerItem>();
    result->registerItem<LayerItem>();
    result->registerItem<ParticleLayoutItem>();
    result->registerItem<InterferenceFunctionItem>();
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
    auto layer = insertItem<LayerItem>(assembly);
    auto layout = insertItem<ParticleLayoutItem>(layer, LayerItem::T_LAYOUTS);
    insertItem<InterferenceFunctionItem>(layout, ParticleLayoutItem::T_INTERFERENCE);
    insertItem<LayerItem>(multilayer);
}
