// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "samplemodel.h"
#include "item_constants.h"
#include "itemcatalogue.h"
#include "items.h"

using namespace ModelView;

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<MultiLayer>();
    result->registerItem<LayerItem>();
    result->registerItem<ParticleItem>();
    result->registerItem<InterferenceFunctionItem>();
    result->registerItem<SphereItem>();
    result->registerItem<CylinderItem>();
    result->registerItem<AnysoPyramidItem>();
    result->registerItem<ShapeGroupItem>();
    return result;
}
} // namespace

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
    init_model();
}

//! Provides initial model content.

void SampleModel::init_model()
{
    auto multi_layer = insertItem<MultiLayer>();
    auto layer = insertItem<LayerItem>(multi_layer);
    insertItem<ParticleItem>(layer);

    insertItem<LayerItem>(multi_layer);

    insertItem<InterferenceFunctionItem>();
}
