// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVariant>
#include <layereditorcore/materialmodel.h>
#include <layereditorcore/samplemodel.h>
#include <mvvm/model/externalproperty.h>
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

const std::string MultiLayerType = "MultiLayer";
const std::string LayerType = "Layer";

} // namespace

using namespace ModelView;

LayerItem::LayerItem() : CompoundItem(LayerType)
{
    addProperty(P_NAME, "Layer")->setDisplayName("Name");
    addProperty(P_MATERIAL, MaterialModel::undefined_material())->setDisplayName("Material");
    addProperty(P_THICKNESS, 42.0)->setDisplayName("Thickness");
}

MultiLayerItem::MultiLayerItem() : CompoundItem(MultiLayerType)
{
    addProperty(P_NREPETITIONS, 1)->setDisplayName("Nr.");
    std::vector<std::string> allowed_child = {MultiLayerType, LayerType};
    registerTag(TagInfo::universalTag(T_LAYERS, allowed_child), /*set_default*/ true);
}

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
