// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "propertyviewmodelcontroller.h"
#include "groupitem.h"
#include "childrenstrategies.h"
#include "labeldatarowconstructor.h"

using namespace ModelView;

PropertyViewModelController::PropertyViewModelController(AbstractViewModel* view_model)
    : ViewModelController(view_model)
{
    setRowConstructor(std::make_unique<LabelDataRowConstructor>());
    setChildrenStrategy(std::make_unique<PropertyItemsStrategy>());
}

//! Generates necessary notifications on SessionItem's data change.

void PropertyViewModelController::onDataChange(SessionItem* item, int role)
{
    ViewModelController::onDataChange(item, role);

    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        ViewModelController::onRowRemoved(group, "", 0);
}
