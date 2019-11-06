// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/standarditems/containeritem.h>

using namespace ModelView;

ContainerItem::ContainerItem() : CompoundItem(Constants::ContainerItemType)
{
    registerTag(ModelView::TagInfo::universalTag(T_ITEMS), /*set_as_default*/ true);
}
