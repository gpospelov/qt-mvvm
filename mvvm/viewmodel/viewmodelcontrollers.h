// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODELCONTROLLERS_H
#define MVVM_VIEWMODELCONTROLLERS_H

#include "abstractviewmodelcontroller.h"
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
    PropertyTableViewModelController(AbstractViewModel* view_model,
                                     const std::vector<std::string>& labels);
};

} // namespace ModelView

#endif // MVVM_VIEWMODELCONTROLLERS_H
