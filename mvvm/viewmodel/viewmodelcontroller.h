// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODELCONTROLLER_H
#define MVVM_VIEWMODELCONTROLLER_H

#include "mvvm_global.h"
#include <memory>

namespace ModelView
{

class AbstractViewModel;

/*!
@class ViewModelController
@brief Syncronizes AbstractViewModel and SessionModel.
*/

class CORE_EXPORT ViewModelController
{
public:
    ViewModelController(AbstractViewModel* view_model);
    virtual ~ViewModelController();

private:
    class ViewModelControllerPrivate;
    std::unique_ptr<ViewModelControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODELCONTROLLER_H
