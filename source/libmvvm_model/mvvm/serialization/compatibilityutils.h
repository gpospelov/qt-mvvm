// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_COMPATIBILITYUTILS_H
#define MVVM_SERIALIZATION_COMPATIBILITYUTILS_H

//! @file compatibilityutils.h
//! @brief Place for utils to fix back compatibility of serialized projects.

#include <memory>
#include <mvvm/model_export.h>

namespace ModelView
{

class SessionItemData;

namespace Compatibility
{

//! Create SessionItemData by combining two sources, runtime and persistent.
//! See explanations in the code.

MVVM_MODEL_EXPORT std::unique_ptr<SessionItemData>
CombineItemData(const SessionItemData& runtime, const SessionItemData& persistent);

} // namespace Compatibility

} // namespace ModelView

#endif // MVVM_SERIALIZATION_COMPATIBILITYUTILS_H
