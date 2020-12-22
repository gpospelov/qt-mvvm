// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_VIEWMODELCONTROLLERFACTORY_H
#define MVVM_FACTORIES_VIEWMODELCONTROLLERFACTORY_H

#include "mvvm/factories/viewmodelcontrollerbuilder.h"
#include "mvvm/viewmodel_export.h"
#include <memory>

namespace ModelView {

class SessionModel;
class ViewModelBase;
class ViewModelController;

namespace Factory {

//! Create universal controller.

template <typename ChildrenStrategy, typename RowStrategy>
std::unique_ptr<ViewModelController> CreateController(SessionModel* session_model,
                                                      ViewModelBase* view_model)
{
    return ViewModelControllerBuilder()
        .model(session_model)
        .viewModel(view_model)
        .childrenStrategy(std::make_unique<ChildrenStrategy>())
        .rowStrategy(std::make_unique<RowStrategy>());
}

} // namespace Factory

} // namespace ModelView

#endif // MVVM_FACTORIES_VIEWMODELCONTROLLERFACTORY_H
