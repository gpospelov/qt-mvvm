// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/itemutils.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionitemcontainer.h"
#include "mvvm/model/sessionitemtags.h"
#include "mvvm/utils/containerutils.h"
#include <iterator>

using namespace ModelView;

void Utils::iterate(SessionItem* item, const std::function<void(SessionItem*)>& fun)
{
    if (item)
        fun(item);
    else
        return;

    for (auto child : item->children())
        iterate(child, fun);
}

void Utils::iterate_if(const SessionItem* item, const std::function<bool(const SessionItem*)>& fun)
{
    bool proceed_with_children(true);

    if (item)
        proceed_with_children = fun(item);

    if (!item || !proceed_with_children)
        return;

    for (auto child : item->children())
        iterate_if(child, fun);
}

int Utils::CopyNumber(const SessionItem* item)
{
    int result(-1);

    if (!item)
        return result;

    int count(0);
    auto model_type = item->modelType();
    if (auto parent = item->parent()) {
        for (auto child : parent->children()) {
            if (child == item)
                result = count;
            if (child->modelType() == model_type)
                ++count;
        }
    }

    return count > 1 ? result : -1;
}

SessionItem* Utils::ChildAt(const SessionItem* parent, int index)
{
    if (!parent)
        return nullptr;

    auto container = parent->children();
    return index >= 0 && static_cast<size_t>(index) < container.size()
               ? container[static_cast<size_t>(index)]
               : nullptr;
}

int Utils::IndexOfChild(const SessionItem* parent, const SessionItem* child)
{
    return Utils::IndexOfItem(parent->children(), child);
}

bool Utils::HasTag(const SessionItem& item, const std::string& tag)
{
    return item.itemTags()->isTag(tag);
}

bool Utils::IsSinglePropertyTag(const SessionItem& item, const std::string& tag)
{
    return item.itemTags()->isSinglePropertyTag(tag);
}

std::vector<std::string> Utils::RegisteredTags(const SessionItem& item)
{
    std::vector<std::string> result;
    for (const auto container : *item.itemTags())
        result.push_back(container->name());
    return result;
}

std::vector<std::string> Utils::RegisteredUniversalTags(const SessionItem& item)
{
    std::vector<std::string> result;
    for (const auto& tag : RegisteredTags(item))
        if (!IsSinglePropertyTag(item, tag))
            result.push_back(tag);
    return result;
}

std::vector<SessionItem*> Utils::TopLevelItems(const SessionItem& item)
{
    std::vector<SessionItem*> result;
    for (auto child : item.children())
        if (child->isVisible() && !IsSinglePropertyTag(item, item.tagRowOfItem(child).tag))
            result.push_back(child);
    return result;
}

std::vector<SessionItem*> Utils::SinglePropertyItems(const SessionItem& item)
{
    std::vector<SessionItem*> result;
    for (auto child : item.children())
        if (child->isVisible() && IsSinglePropertyTag(item, item.tagRowOfItem(child).tag))
            result.push_back(child);
    return result;
}

SessionItem* Utils::FindNextSibling(SessionItem* item)
{
    auto parent = item ? item->parent() : nullptr;
    if (!parent)
        return nullptr;
    auto tagrow = item->tagRow();
    return parent->getItem(tagrow.tag, tagrow.row + 1);
}

SessionItem* Utils::FindPreviousSibling(SessionItem* item)
{
    auto parent = item ? item->parent() : nullptr;
    if (!parent)
        return nullptr;
    auto tagrow = parent->tagRowOfItem(item);
    return parent->getItem(tagrow.tag, tagrow.row - 1);
}

SessionItem* Utils::FindNextItemToSelect(SessionItem* item)
{
    auto next = FindNextSibling(item);
    auto closest = next ? next : FindPreviousSibling(item);
    return closest ? closest : item->parent();
}

bool Utils::IsItemAncestor(const SessionItem* item, const SessionItem* candidate)
{
    if (!item || !candidate)
        return false;
    const SessionItem* parent = item->parent();
    while (parent) {
        if (parent == candidate)
            return true;
        else
            parent = parent->parent();
    }
    return false;
}

std::vector<SessionItem*> Utils::UniqueItems(const std::vector<SessionItem*>& items)
{
    auto filtered = Utils::UniqueWithOrder(items);
    std::vector<SessionItem*> result;
    std::copy_if(filtered.begin(), filtered.end(), std::back_inserter(result),
                 [](auto x) { return x != nullptr; });
    return result;
}
