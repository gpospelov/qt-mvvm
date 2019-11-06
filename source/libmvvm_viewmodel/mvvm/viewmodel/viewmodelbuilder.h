// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELBUILDER_H
#define MVVM_VIEWMODEL_VIEWMODELBUILDER_H

#include <mvvm/core/export.h>
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

#endif  // MVVM_VIEWMODEL_VIEWMODELBUILDER_H
