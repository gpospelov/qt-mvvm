// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/abstractviewmodelcontroller.h>
#include <mvvm/viewmodel/viewmodelbuilder.h>

using namespace ModelView;

struct ViewModelBuilder::ViewModelBuilderImpl {
    ViewModelBuilderImpl() : m_session_model(nullptr) {}
    std::unique_ptr<AbstractViewModelController> m_controller;
    SessionModel* m_session_model;
};

ViewModelBuilder::ViewModelBuilder() : p_impl(std::make_unique<ViewModelBuilderImpl>()) {}

ViewModelBuilder::~ViewModelBuilder() = default;

ViewModelBuilder& ViewModelBuilder::setSessionModel(SessionModel* session_model)
{
    p_impl->m_session_model = session_model;
    return *this;
}

ViewModelBuilder&
ViewModelBuilder::setController(std::unique_ptr<AbstractViewModelController> controller)
{
    p_impl->m_controller = std::move(controller);
    return *this;
}

std::unique_ptr<AbstractViewModel> ViewModelBuilder::build() const
{
    auto result = std::make_unique<AbstractViewModel>(std::move(p_impl->m_controller));
    result->setSessionModel(p_impl->m_session_model);
    return result;
}
