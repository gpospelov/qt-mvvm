// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_STANDARDITEMCATALOGUE_H
#define MVVM_FACTORIES_STANDARDITEMCATALOGUE_H

#include <mvvm/model/itemcatalogue.h>

namespace ModelView
{

MVVM_MODEL_EXPORT std::unique_ptr<ItemCatalogue> CreateStandardItemCatalogue();

}

#endif // MVVM_FACTORIES_STANDARDITEMCATALOGUE_H
