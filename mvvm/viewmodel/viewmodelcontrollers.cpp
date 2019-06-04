// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodelcontrollers.h"
#include "groupitem.h"
#include "childrenstrategies.h"
#include "labeldatarowconstructor.h"

using namespace ModelView;

// ----------------------------------------------------------------------------

TopItemsViewModelController::TopItemsViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowConstructor(std::make_unique<LabelDataRowConstructor>());
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
}

// ----------------------------------------------------------------------------

PropertyViewModelController::PropertyViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowConstructor(std::make_unique<LabelDataRowConstructor>());
    setChildrenStrategy(std::make_unique<PropertyItemsStrategy>());
}

void PropertyViewModelController::onDataChange(SessionItem* item, int role)
{
    AbstractViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        AbstractViewModelController::onRowRemoved(group, "", 0);
}
