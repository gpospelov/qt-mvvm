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
#include "childrenstrategies.h"
#include "labeldatarowconstructor.h"

using namespace ModelView;

PropertyViewModel::PropertyViewModel(SessionModel* model, QObject* parent)
    : AbstractViewModel(parent)
{
    setRowConstructor(std::make_unique<LabelDataRowConstructor>());
    setChildrenStrategy(std::make_unique<PropertyItemsStrategy>());
    setSessionModel(model);
}

//! Generates necessary notifications on SessionItem's data change.

void PropertyViewModel::onDataChange(SessionItem* item, int role)
{
    AbstractViewModel::onDataChange(item, role);

    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        AbstractViewModel::onRowRemoved(group, "", 0);
}
