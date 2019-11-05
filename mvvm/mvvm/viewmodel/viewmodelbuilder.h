// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODELBUILDER_H
#define MVVM_VIEWMODELBUILDER_H

#include <mvvm/viewmodel/abstractviewmodel.h>
#include <memory>

namespace ModelView
{

class SessionModel;
class AbstractViewModel;
class AbstractViewModelController;

/*!
@class ViewModelBuilder
@brief Utility class to build the AbstractViewModel using controller and SessionModel.
*/

class CORE_EXPORT ViewModelBuilder
{
public:
    ViewModelBuilder();
    ~ViewModelBuilder();

    ViewModelBuilder& setSessionModel(SessionModel* session_model);

    ViewModelBuilder& setController(std::unique_ptr<AbstractViewModelController> controller);

    std::unique_ptr<AbstractViewModel> build() const;

private:
    struct ViewModelBuilderImpl;
    std::unique_ptr<ViewModelBuilderImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODELBUILDER_H
