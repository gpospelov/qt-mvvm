// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_STANDARDVIEWMODELCONTROLLERS_H
#define MVVM_VIEWMODEL_STANDARDVIEWMODELCONTROLLERS_H

#include <mvvm/viewmodel/viewmodelcontroller.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <string>
#include <vector>

/*!
@file viewmodelcontrollers.h
Collection of standard controllers for AbstractViewModel.
*/

namespace ModelView
{

/*!
@class DefaultViewModelController
@brief Controller for AbstractViewModel to show all items of SessionModel.

The layout corresponds to original SessionModel, generates standard label/value tree.
*/

class MVVM_VIEWMODEL_EXPORT DefaultViewModelController : public ViewModelController
{
public:
    explicit DefaultViewModelController(SessionModel* session_model, ViewModelBase* view_model);
};

/*!
@class TopItemsViewModelController
@brief Controller for AbstractViewModel to show top level items.

Shows only top level items, property items, group items are hidden.
*/

class MVVM_VIEWMODEL_EXPORT TopItemsViewModelController : public ViewModelController
{
public:
    explicit TopItemsViewModelController(SessionModel* session_model, ViewModelBase* view_model);
};

/*!
@class PropertyViewModelController
@brief Controller for AbstractViewModel to show item properties.

Shows property items, hides top level items, hides inactive items of GroupProperty.
*/

class MVVM_VIEWMODEL_EXPORT PropertyViewModelController : public ViewModelController
{
public:
    explicit PropertyViewModelController(SessionModel* session_model, ViewModelBase* view_model);

protected:
    void onDataChange(SessionItem* item, int role) override;
};

/*!
@class PropertyTableViewModelController
@brief Controller for AbstractViewModel to show item properties in table layout.

Shows all property items and place them in table columns.
FIXME What to do with group property?
*/

class MVVM_VIEWMODEL_EXPORT PropertyTableViewModelController : public ViewModelController
{
public:
    PropertyTableViewModelController(SessionModel* session_model, ViewModelBase* view_model,
                                     const std::vector<std::string>& labels = {});
};

/*!
@class PropertyFlatViewModelController
@brief Controller for AbstractViewModel to show item properties.

Shows property items, hides top level items, hides inactive items of GroupProperty,
moves subproperties of group item under parent of group item.
*/

class MVVM_VIEWMODEL_EXPORT PropertyFlatViewModelController : public ViewModelController
{
public:
    explicit PropertyFlatViewModelController(SessionModel* session_model, ViewModelBase* view_model);

protected:
    void onDataChange(SessionItem* item, int role) override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDVIEWMODELCONTROLLERS_H
