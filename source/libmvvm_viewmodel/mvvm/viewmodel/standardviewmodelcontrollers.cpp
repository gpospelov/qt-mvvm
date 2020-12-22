// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/standardviewmodelcontrollers.h"
#include "mvvm/model/groupitem.h"
#include "mvvm/viewmodel/labeldatarowstrategy.h"
#include "mvvm/viewmodel/propertiesrowstrategy.h"
#include "mvvm/viewmodel/standardchildrenstrategies.h"
#include "mvvm/viewmodel/standardviewitems.h"

using namespace ModelView;

// ----------------------------------------------------------------------------

DefaultViewModelController::DefaultViewModelController(SessionModel* session_model,
                                                       ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<AllChildrenStrategy>());
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

TopItemsViewModelController::TopItemsViewModelController(SessionModel* session_model,
                                                         ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

PropertyViewModelController::PropertyViewModelController(SessionModel* session_model,
                                                         ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<PropertyItemsStrategy>());
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
}

void PropertyViewModelController::onDataChange(SessionItem* item, int role)
{
    ViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        update_branch(group);
}

// ----------------------------------------------------------------------------

// FIXME What to do with group property?

PropertyTableViewModelController::PropertyTableViewModelController(
    SessionModel* session_model, ViewModelBase* view_model, const std::vector<std::string>& labels)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
    setRowStrategy(std::make_unique<PropertiesRowStrategy>(labels));
}

// ----------------------------------------------------------------------------

PropertyFlatViewModelController::PropertyFlatViewModelController(SessionModel* session_model,
                                                                 ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<PropertyItemsFlatStrategy>());
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
}

void PropertyFlatViewModelController::onDataChange(SessionItem* item, int role)
{
    ViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        update_branch(group->parent());
}
