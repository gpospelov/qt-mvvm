// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/groupitem.h>
#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/viewmodel/propertiesrowstrategy.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

// ----------------------------------------------------------------------------

DefaultViewModelController::DefaultViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
    setChildrenStrategy(std::make_unique<AllChildrenStrategy>());
}

// ----------------------------------------------------------------------------

TopItemsViewModelController::TopItemsViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
}

// ----------------------------------------------------------------------------

PropertyViewModelController::PropertyViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
    setChildrenStrategy(std::make_unique<PropertyItemsStrategy>());
}

void PropertyViewModelController::onDataChange(SessionItem* item, int role)
{
    AbstractViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        AbstractViewModelController::onItemRemoved(group, {"", 0});
}

// ----------------------------------------------------------------------------

PropertyTableViewModelController::PropertyTableViewModelController(
    AbstractViewModel* view_model, const std::vector<std::string>& labels)
    : AbstractViewModelController(view_model)
{
    setRowStrategy(std::make_unique<PropertiesRowStrategy>(labels));
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
}

// ----------------------------------------------------------------------------

PropertyFlatViewModelController::PropertyFlatViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
    setChildrenStrategy(std::make_unique<PropertyItemsFlatStrategy>());
}

void PropertyFlatViewModelController::onDataChange(SessionItem* item, int role)
{
    AbstractViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        AbstractViewModelController::onItemRemoved(group->parent(), {"", 0});
}
