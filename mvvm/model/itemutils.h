// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMUTILS_H
#define MVVM_ITEMUTILS_H

#include "mvvm_global.h"
#include <functional>
#include <vector>

class QVariant;

namespace ModelView {

class SessionItem;

namespace Utils
{

//! Iterates through item and all its children.
CORE_EXPORT void iterate(SessionItem* item, const std::function<void(SessionItem*)>& fun);

//! Iterates through all model indices and calls user function.
//! If function returns false for given index, iteration will not go down to children.
CORE_EXPORT void iterate_if(const SessionItem* item, const std::function<bool(const SessionItem*)>& fun);

//! Returns copy number of given item in it's parent hierarchy. Takes into account only items with
//! same modelType.
CORE_EXPORT int CopyNumber(const SessionItem* item);

//! Returns child at given index of parent. No tags are involved, index is considered
//! as global index in the combined array of all children.
CORE_EXPORT SessionItem* ChildAt(const SessionItem* parent, int index);

//! Returns index in children array corresponding to given child. No tags are involved,
//! index is considered as global index in the combined array of all children.
CORE_EXPORT int IndexOfChild(const SessionItem* parent, SessionItem* child);

//! Returns vector of children representing top level items.

CORE_EXPORT std::vector<SessionItem*> TopLevelItems(const SessionItem& item);

//! Returns vector of children representing property items.

CORE_EXPORT std::vector<SessionItem*> SinglePropertyItems(const SessionItem& item);

}  // namespace Utils

}  // namespace ModelView

#endif // MVVM_ITEMUTILS_H

