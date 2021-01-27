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

#include "mvvm/model_export.h"

namespace ModelView {

class SessionItemContainer;
class TagInfo;

namespace Compatibility {

//! Returns `true` if given TagInfo is compatible with given container.
//! See explanations in the code.

MVVM_MODEL_EXPORT
bool IsCompatibleUniversalTag(const SessionItemContainer& container, const TagInfo& taginfo);

//! Returns `true` if given TagInfo is a single property tag which is compatible with given
//! container. See more explanations in the code.

MVVM_MODEL_EXPORT
bool IsCompatibleSinglePropertyTag(const SessionItemContainer& container, const TagInfo& taginfo);

//! Returns `true` if given TagInfo is a tag from GroupItem which is compatible with given
//! container. See more explanations in the code.

MVVM_MODEL_EXPORT bool IsCompatibleGroupTag(const SessionItemContainer& container,
                                            const TagInfo& taginfo);

} // namespace Compatibility

} // namespace ModelView

#endif // MVVM_SERIALIZATION_COMPATIBILITYUTILS_H
