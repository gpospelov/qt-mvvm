// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMUTILS_H
#define ITEMUTILS_H

#include "global.h"
#include <functional>

class QVariant;

namespace ModelView {

class SessionItem;

namespace Utils
{

//! Iterates through item and all its children.
CORE_EXPORT void iterate(const SessionItem* item, const std::function<void(const SessionItem*)>& fun);

//! Iterates through all model indices and calls user function.
//! If function returns false for given index, iteration will not go down to children.
CORE_EXPORT void iterate_if(const SessionItem* item, const std::function<bool(const SessionItem*)>& fun);

//! Returns type of variant (additionally checks for user type).
CORE_EXPORT int VariantType(const QVariant& variant);

//! Returns true if variants has compatible types.
CORE_EXPORT bool CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue);

//! Returns true if given variants have same type and value.
CORE_EXPORT bool IsTheSame(const QVariant& var1, const QVariant& var2);

//! Returns copy number of given item in it's parent hierarchy. Takes into account only items with
//! same modelType.
CORE_EXPORT int CopyNumber(const SessionItem* item);

//! Returns child at given index of parent. No tags are involved, index is concidered
//! as global index in the array with all children.
CORE_EXPORT SessionItem* ChildAt(const SessionItem* parent, int index);

//! Returns index in children array corresponding to given child. No tags involved.
CORE_EXPORT int IndexOfChild(const SessionItem* parent, SessionItem* child);

}  // namespace Utils

}  // namespace ModelView

#endif
