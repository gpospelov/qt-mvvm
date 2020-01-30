// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "layeritems.h"
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
}

//! Populate the model with default MultiLayer with 3 layers.

void SampleModel::create_default_multilayer()
{
    auto multilayer = insertItem<MultiLayerItem>();

    auto top = insertItem<LayerItem>(multilayer);
    top->setDisplayName("Ambient");
    top->setProperty(LayerItem::P_THICKNESS, 0.0);

    auto middle = insertItem<LayerItem>(multilayer);
    middle->setDisplayName("Middle");
    middle->setProperty(LayerItem::P_THICKNESS, 42.0);

    auto substrate = insertItem<LayerItem>(multilayer);
    substrate->setDisplayName("Substrate");
    substrate->setProperty(LayerItem::P_THICKNESS, 0.0);
}
