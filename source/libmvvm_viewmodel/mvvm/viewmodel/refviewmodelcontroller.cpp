// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/childrenstrategyinterface.h>
#include <mvvm/viewmodel/refviewmodel.h>
#include <mvvm/viewmodel/refviewmodelcontroller.h>
#include <mvvm/viewmodel/rowstrategyinterface.h>

using namespace ModelView;

struct RefViewModelController::RefViewModelControllerImpl {
    RefViewModelController* controller;
    SessionModel* session_model{nullptr};
    ViewModel* view_model{nullptr};
    std::unique_ptr<ChildrenStrategyInterface> m_children_strategy;
    std::unique_ptr<RowStrategyInterface> m_row_strategy;
    RefViewModelControllerImpl(RefViewModelController* controller, SessionModel* session_model,
                               ViewModel* view_model)
        : controller(controller), session_model(session_model), view_model(view_model)
    {
    }
};

RefViewModelController::RefViewModelController(SessionModel* session_model, ViewModel* view_model)
    : p_impl(std::make_unique<RefViewModelControllerImpl>(this, session_model, view_model))
{
}

RefViewModelController::~RefViewModelController() = default;

void RefViewModelController::setChildrenStrategy(
    std::unique_ptr<ChildrenStrategyInterface> children_strategy)
{
    p_impl->m_children_strategy = std::move(children_strategy);
}

void RefViewModelController::setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy)
{
    p_impl->m_row_strategy = std::move(row_strategy);
}

//! Returns SessionModel handled by this controller.

SessionModel* RefViewModelController::sessionModel() const
{
    return p_impl->session_model;
}
