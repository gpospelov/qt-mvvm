// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemutils.h"
#include "sessionitem.h"
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
    auto container = parent->children();
    auto pos = find(container.begin(), container.end(), child);
    return pos == container.end() ? -1 : static_cast<int>(std::distance(container.begin(), pos));
}

std::vector<SessionItem*> Utils::TopLevelItems(const SessionItem& item)
{
    std::vector<SessionItem*> result;
    for (auto child : item.children())
        if (!item.isSinglePropertyTag(item.tagFromItem(child)))
            result.push_back(child);
    return result;
}

std::vector<SessionItem*> Utils::SinglePropertyItems(const SessionItem& item)
{
    std::vector<SessionItem*> result;
    for (auto child : item.children())
        if (item.isSinglePropertyTag(item.tagFromItem(child)))
            result.push_back(child);
    return result;
}
