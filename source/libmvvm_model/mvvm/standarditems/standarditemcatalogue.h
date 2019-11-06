// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_STANDARDITEMCATALOGUE_H
#define MVVM_STANDARDITEMS_STANDARDITEMCATALOGUE_H

#include <mvvm/model/itemcatalogue.h>

namespace ModelView
{

CORE_EXPORT std::unique_ptr<ItemCatalogue> CreateStandardItemCatalogue();

}

#endif  // MVVM_STANDARDITEMS_STANDARDITEMCATALOGUE_H
