// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/standarditems/containeritem.h>

using namespace ModelView;

ContainerItem::ContainerItem() : CompoundItem(Constants::ContainerItemType)
{
    registerTag(ModelView::TagInfo::universalTag(T_ITEMS), /*set_as_default*/ true);
}
