// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PROPERTYVIEWMODELCONTROLLER_H
#define MVVM_PROPERTYVIEWMODELCONTROLLER_H

#include "abstractviewmodelcontroller.h"

namespace ModelView
{

//! View model to show content of SessionModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class CORE_EXPORT PropertyViewModelController : public AbstractViewModelController
{
public:
    PropertyViewModelController(AbstractViewModel* view_model);

protected:
    void onDataChange(SessionItem* item, int role) override;
};

} // namespace ModelView

#endif // MVVM_PROPERTYVIEWMODELCONTROLLER_H
