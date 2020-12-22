// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_ITEMCONVERTERFACTORY_H
#define MVVM_FACTORIES_ITEMCONVERTERFACTORY_H

//! @file itemconverterfactory.h
//! Collection of factory functions to create SessionItem converters to/from serialized content.

#include "mvvm/serialization/jsonitemconverterinterface.h"
#include <memory>

namespace ModelView {

class ItemFactoryInterface;

//! Creates JSON item converter intended for item cloning.

MVVM_MODEL_EXPORT std::unique_ptr<JsonItemConverterInterface>
CreateItemCloneConverter(const ItemFactoryInterface* item_factory);

//! Creates JSON item converter intended for item copying.

MVVM_MODEL_EXPORT std::unique_ptr<JsonItemConverterInterface>
CreateItemCopyConverter(const ItemFactoryInterface* item_factory);

//! Creates JSON item converter intended for saving on disk.

MVVM_MODEL_EXPORT std::unique_ptr<JsonItemConverterInterface>
CreateItemProjectConverter(const ItemFactoryInterface* item_factory);

} // namespace ModelView

#endif // MVVM_FACTORIES_ITEMCONVERTERFACTORY_H
