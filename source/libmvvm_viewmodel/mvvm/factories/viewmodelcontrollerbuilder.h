// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_VIEWMODELCONTROLLERBUILDER_H
#define MVVM_FACTORIES_VIEWMODELCONTROLLERBUILDER_H

#include "mvvm/viewmodel/viewmodelcontroller.h"
#include "mvvm/viewmodel_export.h"
#include <memory>

namespace ModelView {

class SessionModel;
class ViewModelBase;
class ChildrenStrategyInterface;
class RowStrategyInterface;

//! Builder class for ViewModelController.

class MVVM_VIEWMODEL_EXPORT ViewModelControllerBuilder {
public:
    using self = ViewModelControllerBuilder;

    ViewModelControllerBuilder();
    ~ViewModelControllerBuilder();

    ViewModelControllerBuilder(const ViewModelControllerBuilder& other) = delete;
    ViewModelControllerBuilder& operator=(const ViewModelControllerBuilder& other) = delete;

    self& model(SessionModel* model);
    self& viewModel(ViewModelBase* view_model);
    self& childrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);
    self& rowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy);

    operator std::unique_ptr<ViewModelController>();

private:
    //! Components necessary to build ViewModelController
    struct Context {
        SessionModel* model{nullptr};
        ViewModelBase* view_model{nullptr};
        std::unique_ptr<ChildrenStrategyInterface> children_strategy;
        std::unique_ptr<RowStrategyInterface> row_strategy;
    };

    Context context;
};

} // namespace ModelView

#endif // MVVM_FACTORIES_VIEWMODELCONTROLLERBUILDER_H
