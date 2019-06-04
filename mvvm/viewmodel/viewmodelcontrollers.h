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

namespace ModelView {

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


}  // namespace ModelView

#endif // MVVM_VIEWMODELCONTROLLERS_H
