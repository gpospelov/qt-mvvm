// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerItems.h"
#include "MaterialModel.h"
#include "externalproperty.h"
#include "item_constants.h"
#include <QVariant>

using namespace ModelView;

LayerItem::LayerItem() : LocatedItem(::Constants::LayerType)
{
    addProperty(P_NAME, "Layer")->setDisplayName("Name");
    addProperty(P_MATERIAL, MaterialModel::undefined_material())->setDisplayName("Material");
    addProperty(P_THICKNESS, 42.0)->setDisplayName("Thickness");
    registerTag(TagInfo::universalTag(T_LAYOUTS, {::Constants::ParticleLayoutType}),
                /*set_default*/ true);
}

MultiLayerItem::MultiLayerItem() : LocatedItem(::Constants::MultiLayerType)
{
    addProperty(P_NREPETITIONS, 1)->setDisplayName("Nr.");
    std::vector<std::string> allowed_child = {::Constants::MultiLayerType, ::Constants::LayerType};
    registerTag(TagInfo::universalTag(T_LAYERS, allowed_child), /*set_default*/ true);
}
