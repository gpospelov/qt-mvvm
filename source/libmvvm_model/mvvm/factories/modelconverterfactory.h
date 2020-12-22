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

#include "mvvm/serialization/jsonmodelconverterinterface.h"
#include <memory>

namespace ModelView {

//! Creates a JSON model converter intended for model cloning.
MVVM_MODEL_EXPORT std::unique_ptr<JsonModelConverterInterface> CreateModelCloneConverter();

//! Creates a JSON model converter intended for model copying.
MVVM_MODEL_EXPORT std::unique_ptr<JsonModelConverterInterface> CreateModelCopyConverter();

//! Creates a JSON model converter intended for save/load of the project on disk.
MVVM_MODEL_EXPORT std::unique_ptr<JsonModelConverterInterface> CreateModelProjectConverter();

} // namespace ModelView

#endif // MVVM_FACTORIES_MODELCONVERTERFACTORY_H
