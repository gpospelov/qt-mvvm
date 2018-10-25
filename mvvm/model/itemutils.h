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

}  // namespace Utils

}  // namespace ModelView

#endif
