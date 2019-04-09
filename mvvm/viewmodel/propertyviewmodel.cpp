// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "propertyviewmodel.h"
#include "groupitem.h"
#include "viewitem.h"

using namespace ModelView;

PropertyViewModel::PropertyViewModel(QObject* parent)
    : DefaultViewModel(parent)
{

}

//! Generates necessary notifications on SessionItem's data change.
//! If data change occured with GroupItem, performs cleanup and regeneration of
//! ViewItems, corresponding to groupItem's current index.

void PropertyViewModel::onDataChange(SessionItem* item, int role)
{
    DefaultViewModel::onDataChange(item, role);
    if (auto group = dynamic_cast<GroupItem*>(item))
        DefaultViewModel::onRowRemoved(group, "", 0);
}

//! Returns (possibly filtered) vector of children of given item.
//! In the case of GroupItem, shows only underlying properties of active item.

std::vector<SessionItem*> PropertyViewModel::item_children(SessionItem* item)
{
    auto group = dynamic_cast<GroupItem*>(item);
    return group ? group->currentItem()->children() : item->children();
}
