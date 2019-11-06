// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
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
