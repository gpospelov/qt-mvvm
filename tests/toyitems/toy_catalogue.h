// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TOYCATALOGUE_H
#define TOYCATALOGUE_H

#include "defaultitemcatalogue.h"

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{

// ----------------------------------------------------------------------------

//! Returns catalogue of toy items.
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue();

} // namespace ToyItems

#endif // TOYCATALOGUE_H
