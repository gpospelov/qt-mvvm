// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DEFAULTITEMCATALOGUE_H
#define MVVM_DEFAULTITEMCATALOGUE_H

#include "itemcatalogue.h"

namespace ModelView
{

CORE_EXPORT std::unique_ptr<ItemCatalogue> CreateDefaultItemCatalogue();

}

#endif // MVVM_DEFAULTITEMCATALOGUE_H
