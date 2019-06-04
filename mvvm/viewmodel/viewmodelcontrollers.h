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
    DefaultViewModelController(AbstractViewModel* view_model);
};

/*!
@class TopItemsViewModelController
@brief Controller for AbstractViewModel to show top level items.

Shows only top level items, property items, group items are hidden.
*/

class CORE_EXPORT TopItemsViewModelController : public AbstractViewModelController
{
public:
    TopItemsViewModelController(AbstractViewModel* view_model);
};

/*!
@class PropertyViewModelController
@brief Controller for AbstractViewModel to show item properties.

Shows property items, hides top level items, hides inactive items of GroupProperty.
*/

class CORE_EXPORT PropertyViewModelController : public AbstractViewModelController
{
public:
    PropertyViewModelController(AbstractViewModel* view_model);

protected:
    void onDataChange(SessionItem* item, int role) override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODELCONTROLLERS_H
