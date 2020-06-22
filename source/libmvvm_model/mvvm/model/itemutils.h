// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMUTILS_H
#define MVVM_MODEL_ITEMUTILS_H

#include <functional>
#include <mvvm/core/export.h>
#include <vector>

namespace ModelView
{

class SessionItem;

namespace Utils
{

//! Iterates through item and all its children.
MVVM_MODEL_EXPORT void iterate(SessionItem* item, const std::function<void(SessionItem*)>& fun);

//! Iterates through all model indices and calls user function.
//! If function returns false for given index, iteration will not go down to children.
MVVM_MODEL_EXPORT void iterate_if(const SessionItem* item,
                            const std::function<bool(const SessionItem*)>& fun);

//! Returns copy number of given item in it's parent hierarchy. Takes into account only items with
//! same modelType.
MVVM_MODEL_EXPORT int CopyNumber(const SessionItem* item);

//! Returns child at given index of parent. No tags are involved, index is considered
//! as global index in the combined array of all children.
MVVM_MODEL_EXPORT SessionItem* ChildAt(const SessionItem* parent, int index);

//! Returns index in children array corresponding to given child. No tags are involved,
//! index is considered as global index in the combined array of all children.
MVVM_MODEL_EXPORT int IndexOfChild(const SessionItem* parent, const SessionItem* child);

//! Returns vector of children representing top level items.

MVVM_MODEL_EXPORT std::vector<SessionItem*> TopLevelItems(const SessionItem& item);

//! Returns vector of children representing property items.

MVVM_MODEL_EXPORT std::vector<SessionItem*> SinglePropertyItems(const SessionItem& item);

//! Returns next sibling with same tag.

MVVM_MODEL_EXPORT SessionItem* FindNextSibling(SessionItem* item);

//! Returns previous sibling with same tag.

MVVM_MODEL_EXPORT SessionItem* FindPreviousSibling(SessionItem* item);

//! Finds next item to select
//! Method is used in the context of next item selection after given item was deleted.

MVVM_MODEL_EXPORT SessionItem* FindNextItemToSelect(SessionItem* item);

//! Returns true if 'candidate' is one of ancestor of given item.
MVVM_MODEL_EXPORT bool IsItemAncestor(const SessionItem* item, const SessionItem* candidate);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_MODEL_ITEMUTILS_H
