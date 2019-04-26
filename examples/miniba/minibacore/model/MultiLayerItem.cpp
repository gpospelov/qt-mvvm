// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MultiLayerItem.h"
#include "item_constants.h"

const std::string MultiLayerItem::T_LAYERS = "T_LAYERS";
const std::string MultiLayerItem::P_NREPETITIONS = "P_NREPETITIONS";

MultiLayerItem::MultiLayerItem() : ModelView::CompoundItem(Constants::MultiLayerType)
{
    addProperty<ModelView::PropertyItem>(P_NREPETITIONS, 1)->setDisplayName("N");
    registerTag(ModelView::TagInfo::universalTag(T_LAYERS,
                                                 {Constants::MultiLayerType, Constants::LayerType}),
                /*set_as_default*/ true);
}
