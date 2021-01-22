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

#include "mvvm/model_export.h"
#include <functional>
#include <string>
#include <vector>

namespace ModelView {

class SessionItem;

namespace Utils {

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

//! Returns true if given item has registered tag.
MVVM_MODEL_EXPORT bool HasTag(const SessionItem& item, const std::string& tag);

//! Returns true if given item has registered `tag`, and it belongs to single property.
MVVM_MODEL_EXPORT bool IsSinglePropertyTag(const SessionItem& item, const std::string& tag);

//! Returns vector of strings containing all registered tags of the given item.
MVVM_MODEL_EXPORT std::vector<std::string> RegisteredTags(const SessionItem& item);

//! Returns vector of strings containing all registered universal tags of the given item.
//! A universal tag is a tag that is usually empty after item construction and serves for later
//! children's insertion.
MVVM_MODEL_EXPORT std::vector<std::string> RegisteredUniversalTags(const SessionItem& item);

//! Returns vector of all visible children representing top level items.
MVVM_MODEL_EXPORT std::vector<SessionItem*> TopLevelItems(const SessionItem& item);

//! Returns vector of all visible children representing property items.
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

//! Returns vector with duplicates and 'nullptr' filtered out.
MVVM_MODEL_EXPORT std::vector<SessionItem*> UniqueItems(const std::vector<SessionItem*>& items);

//! Returns vector of items casted to given type.
template <typename T> std::vector<T*> CastedItems(const std::vector<SessionItem*>& items)
{
    std::vector<T*> result;
    for (auto item : items)
        if (auto casted_item = dynamic_cast<T*>(item); casted_item)
            result.push_back(casted_item);

    return result;
}

} // namespace Utils

} // namespace ModelView

#endif // MVVM_MODEL_ITEMUTILS_H
