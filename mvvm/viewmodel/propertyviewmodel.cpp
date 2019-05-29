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
#include "itemutils.h"
#include "childrenstrategies.h"

using namespace ModelView;

PropertyViewModel::PropertyViewModel(SessionModel* model, QObject* parent)
    : DefaultViewModel(model, parent)
{
    setChildrenStrategy(std::make_unique<PropertyItemsStrategy>());
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
