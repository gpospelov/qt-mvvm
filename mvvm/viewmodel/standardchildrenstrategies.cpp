// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "standardchildrenstrategies.h"
#include "itemutils.h"
#include "groupitem.h"

using namespace ModelView;

std::vector<SessionItem*> AllChildrenStrategy::children(const SessionItem* item) const
{
    return item ? item->children() : std::vector<SessionItem*>();
}


std::vector<SessionItem*> TopItemsStrategy::children(const SessionItem* item) const
{
    return item ? Utils::TopLevelItems(*item) : std::vector<SessionItem*>();
}

std::vector<SessionItem*> PropertyItemsStrategy::children(const SessionItem* item) const
{
    if (!item)
        return std::vector<SessionItem*>();

    auto group = dynamic_cast<const GroupItem*>(item);
    auto next_item = group ? group->currentItem() : item;
    return Utils::SinglePropertyItems(*next_item);
}
