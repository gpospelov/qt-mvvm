// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMCATALOGUE_H
#define ITEMCATALOGUE_H

#include "itemcatalogue.h"

//! Returns catalogue of toy items.
CORE_EXPORT std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue();

#endif //  ITEMCATALOGUE_H
