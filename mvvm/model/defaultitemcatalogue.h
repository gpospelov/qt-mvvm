// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef DEFAULTITEMCATALOGUE_H
#define DEFAULTITEMCATALOGUE_H

#include "itemcatalogue.h"

namespace ModelView
{

CORE_EXPORT std::unique_ptr<ItemCatalogue> CreateDefaultItemCatalogue();

}

#endif // DEFAULTITEMCATALOGUE_H
