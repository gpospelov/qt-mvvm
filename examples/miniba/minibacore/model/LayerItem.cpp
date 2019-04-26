// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerItem.h"
#include "item_constants.h"

const std::string LayerItem::P_THICKNESS = "P_THICKNESS";

LayerItem::LayerItem() : ModelView::CompoundItem(Constants::LayerType)
{
    addProperty<ModelView::PropertyItem>(P_THICKNESS, 42.0)->setDisplayName("Thickness");
}
