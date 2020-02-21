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
#include <mvvm/viewmodel/refviewitems.h>
#include <mvvm/viewmodel/refviewmodel.h>
#include <mvvm/viewmodel/refviewmodelcontroller.h>
#include <mvvm/viewmodel/rowstrategyinterface.h>

using namespace ModelView;

struct RefViewModelController::RefViewModelControllerImpl {
    RefViewModelController* controller;
    SessionModel* session_model{nullptr};
    RefViewModel* view_model{nullptr};
    std::unique_ptr<ChildrenStrategyInterface> children_strategy;
    std::unique_ptr<RowStrategyInterface> row_strategy;

    RefViewModelControllerImpl(RefViewModelController* controller, SessionModel* session_model,
                               RefViewModel* view_model)
        : controller(controller), session_model(session_model), view_model(view_model)
    {
    }

    void check_initialization()
    {
        const std::string msg("Error in RefViewModelController: ");
        if (!view_model)
            throw std::runtime_error(msg + "ViewModel is not defined");

        if (!session_model)
            throw std::runtime_error(msg + "SessionModel is not defined");

        if (!row_strategy)
            throw std::runtime_error(msg + "RowStrategy is not defined");

        if (!children_strategy)
            throw std::runtime_error(msg + "Children is not defined");
    }

    void init_view_model()
    {
        check_initialization();
        view_model->clear();
        iterate(controller->rootSessionItem(), view_model->rootItem());
        // update labels
    }

    void iterate(const SessionItem* item, RefViewItem* parent)
    {
        RefViewItem* origParent(parent);
        for (auto child : children_strategy->children(item)) {
            auto row = row_strategy->constructRefRow(child);
            if (!row.empty()) {
                auto next_parent = row.at(0).get();
                parent->appendRow(std::move(row));
                parent = next_parent; // labelItem
                iterate(child, parent);
            }
            parent = origParent;
        }
    }
};

RefViewModelController::RefViewModelController(SessionModel* session_model,
                                               RefViewModel* view_model)
    : p_impl(std::make_unique<RefViewModelControllerImpl>(this, session_model, view_model))
{
    view_model->setRootViewItem(std::make_unique<RefRootViewItem>(session_model->rootItem()));
}

RefViewModelController::~RefViewModelController() = default;

void RefViewModelController::setChildrenStrategy(
    std::unique_ptr<ChildrenStrategyInterface> children_strategy)
{
    p_impl->children_strategy = std::move(children_strategy);
}

void RefViewModelController::setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy)
{
    p_impl->row_strategy = std::move(row_strategy);
}

//! Returns SessionModel handled by this controller.

SessionModel* RefViewModelController::sessionModel() const
{
    return p_impl->session_model;
}

void RefViewModelController::setRootSessionItem(SessionItem* item)
{
    p_impl->view_model->setRootViewItem(std::make_unique<RefRootViewItem>(item));
}

SessionItem* RefViewModelController::rootSessionItem() const
{
    return p_impl->view_model->rootItem()->item();
}

//! Init controller and update the model.

void RefViewModelController::init()
{
    p_impl->init_view_model();
}
