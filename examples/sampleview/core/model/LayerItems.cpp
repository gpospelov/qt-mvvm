// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerItems.h"
#include "externalproperty.h"
#include "item_constants.h"
#include "MaterialModel.h"
#include <QVariant>

using namespace ModelView;

namespace
{
QVariant material_link()
{
    return QVariant::fromValue(MaterialModel::undefined_material());
}
} // namespace

const std::string LayerItem::P_NAME = "P_NAME";
const std::string LayerItem::P_MATERIAL = "P_MATERIAL";
const std::string LayerItem::P_THICKNESS = "P_THICKNESS";
const std::string LayerItem::T_LAYOUTS = "T_LAYOUTS";

LayerItem::LayerItem() : LocatedItem(::Constants::LayerType)
{
    addProperty<>(P_NAME, "Layer")->setDisplayName("Name");
    addProperty<>(P_MATERIAL, material_link())->setDisplayName("Material");
    addProperty<>(P_THICKNESS, 42.0)->setDisplayName("Thickness");
    registerTag(TagInfo::universalTag(T_LAYOUTS, {::Constants::ParticleLayoutType}));
}

// ----------------------------------------------------------------------------

const std::string MultiLayerItem::T_LAYERS = "T_LAYERS";
const std::string MultiLayerItem::P_NREPETITIONS = "P_NREPETITIONS";

MultiLayerItem::MultiLayerItem() : LocatedItem(::Constants::MultiLayerType)
{
    addProperty<>(P_NREPETITIONS, 1)->setDisplayName("Nr.");
    std::vector<std::string> allowed_child = {::Constants::MultiLayerType, ::Constants::LayerType};
    registerTag(TagInfo::universalTag(T_LAYERS, allowed_child),/*set_default*/true);
}
