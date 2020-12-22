// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/externalproperty.h"
#include <layereditorcore/materialmodel.h>
#include <layereditorcore/samplemodel.h>
#include <QVariant>

using namespace ModelView;

namespace {
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
    registerItem<MultiLayerItem>();
    registerItem<LayerItem>();

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
