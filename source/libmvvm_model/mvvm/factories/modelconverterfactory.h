// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_MODELCONVERTERFACTORY_H
#define MVVM_FACTORIES_MODELCONVERTERFACTORY_H

//! @file modelconverterfactory.h
//! Collection of factory functions to create SessionModel converters to/from serialized content.

#include <memory>
#include <mvvm/serialization/jsonmodelconverterinterface.h>

namespace ModelView
{

//! Creates a JSON model converter intended for model copying.
//! Saves a full deep copy of model in JSON. When restoring, reconstruct full copy and regenerate
//! item's ID to make them unique.

MVVM_MODEL_EXPORT std::unique_ptr<JsonModelConverterInterface> CreateModelCopyConverter();

//! Creates a JSON model converter intended for save/load of the project on disk.
//! When saving to disk, only certain data is saved. When loading from disk, items
//! in memory is gently updated from JSON content. See the description of
//! `CreateItemProjectConverter` for more details.

MVVM_MODEL_EXPORT std::unique_ptr<JsonModelConverterInterface> CreateModelProjectConverter();

} // namespace ModelView

#endif // MVVM_FACTORIES_MODELCONVERTERFACTORY_H
