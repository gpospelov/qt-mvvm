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

#include <mvvm/viewmodel/abstractviewmodelcontroller.h>
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

class CORE_EXPORT DefaultViewModelController : public AbstractViewModelController
{
public:
    explicit DefaultViewModelController(AbstractViewModel* view_model = nullptr);
};

/*!
@class TopItemsViewModelController
@brief Controller for AbstractViewModel to show top level items.

Shows only top level items, property items, group items are hidden.
*/

class CORE_EXPORT TopItemsViewModelController : public AbstractViewModelController
{
public:
    explicit TopItemsViewModelController(AbstractViewModel* view_model = nullptr);
};

/*!
@class PropertyViewModelController
@brief Controller for AbstractViewModel to show item properties.

Shows property items, hides top level items, hides inactive items of GroupProperty.
*/

class CORE_EXPORT PropertyViewModelController : public AbstractViewModelController
{
public:
    explicit PropertyViewModelController(AbstractViewModel* view_model = nullptr);

protected:
    void onDataChange(SessionItem* item, int role) override;
};

/*!
@class PropertyTableViewModelController
@brief Controller for AbstractViewModel to show item properties in table layout.

Shows all property items and place them in table columns.
FIXME What to do with group property?
*/

class CORE_EXPORT PropertyTableViewModelController : public AbstractViewModelController
{
public:
    PropertyTableViewModelController(AbstractViewModel* view_model = nullptr,
                                     const std::vector<std::string>& labels = {});
};

/*!
@class PropertyFlatViewModelController
@brief Controller for AbstractViewModel to show item properties.

Shows property items, hides top level items, hides inactive items of GroupProperty,
moves subproperties of group item under parent of group item.
*/

class CORE_EXPORT PropertyFlatViewModelController : public AbstractViewModelController
{
public:
    explicit PropertyFlatViewModelController(AbstractViewModel* view_model = nullptr);

protected:
    void onDataChange(SessionItem* item, int role) override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDVIEWMODELCONTROLLERS_H
