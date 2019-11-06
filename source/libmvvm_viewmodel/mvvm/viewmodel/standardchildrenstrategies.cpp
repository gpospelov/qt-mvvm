// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/groupitem.h>

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
