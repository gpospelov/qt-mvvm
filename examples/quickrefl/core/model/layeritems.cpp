// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layeritems.h"
#include "materialmodel.h"
#include "item_constants.h"
#include <QVariant>
#include <mvvm/model/externalproperty.h>

LayerItem::LayerItem() : ModelView::CompoundItem(::Constants::LayerItemType)
{
    addProperty(P_NAME, "Layer")->setDisplayName("Name");
    addProperty(P_MATERIAL, MaterialModel::undefined_material())->setDisplayName("Material");
    addProperty(P_THICKNESS, 42.0)->setDisplayName("Thickness");
}

MultiLayerItem::MultiLayerItem() : ModelView::CompoundItem(::Constants::MultiLayerItemType)
{
    addProperty(P_NREPETITIONS, 1)->setDisplayName("Nr.");
    std::vector<std::string> allowed_child = {::Constants::MultiLayerItemType, ::Constants::LayerItemType};
    registerTag(ModelView::TagInfo::universalTag(T_LAYERS, allowed_child), /*set_default*/ true);
}
