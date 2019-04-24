// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMCATALOGUE2_H
#define ITEMCATALOGUE2_H

#include "itemcatalogue.h"

//! Returns catalogue of toy items.
std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue();

#endif //  ITEMCATALOGUE2_H
