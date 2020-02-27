// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDebug>
#include <map>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/modelmapper.h>
#include <mvvm/utils/containerutils.h>
#include <mvvm/viewmodel/childrenstrategyinterface.h>
#include <mvvm/viewmodel/rowstrategyinterface.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <mvvm/viewmodel/viewmodelbase.h>
#include <mvvm/viewmodel/viewmodelcontroller.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

namespace
{

//! Returns true if given SessionItem role is valid for view
bool isValidItemRole(const ViewItem* view, int item_role)
{
    if (view->item_role() == item_role)
        return true;

    if (item_role == ModelView::ItemDataRole::APPEARANCE)
        return true;
    return false;
}

} // namespace

struct ViewModelController::RefViewModelControllerImpl {
    ViewModelController* controller;
    SessionModel* session_model{nullptr};
    ViewModelBase* view_model{nullptr};
    std::unique_ptr<ChildrenStrategyInterface> children_strategy;
    std::unique_ptr<RowStrategyInterface> row_strategy;
    std::map<SessionItem*, ViewItem*> item_to_view; //! correspondence of item and its view

    RefViewModelControllerImpl(ViewModelController* controller, SessionModel* session_model,
                               ViewModelBase* view_model)
        : controller(controller), view_model(view_model)
    {
        setSessionModel(session_model);
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
        item_to_view.clear();
        item_to_view[controller->rootSessionItem()] = view_model->rootItem();
        iterate(controller->rootSessionItem(), view_model->rootItem());
    }

    void iterate(const SessionItem* item, ViewItem* parent)
    {
        ViewItem* origParent(parent);
        for (auto child : children_strategy->children(item)) {
            auto row = row_strategy->constructRefRow(child);
            if (!row.empty()) {
                auto next_parent = row.at(0).get();
                view_model->appendRow(parent, std::move(row));
                item_to_view[child] = next_parent;
                parent = next_parent; // labelItem
                iterate(child, parent);
            }
            parent = origParent;
        }
    }

    //! Remove row of ViewItem's corresponding to given item.

    void remove_row_of_views(SessionItem* item)
    {
        auto pos = item_to_view.find(item);
        if (pos != item_to_view.end()) {
            auto view = pos->second;
            view_model->removeRow(view->parent(), view->row());
            item_to_view.erase(pos);
        }
    }

    void remove_children_of_view(ViewItem* view)
    {
        for (auto child : view->children()) {
            auto pos = std::find_if(item_to_view.begin(), item_to_view.end(),
                                    [child](const auto& it) { return it.second == child; });
            if (pos != item_to_view.end())
                item_to_view.erase(pos);
        }

        view_model->clearRows(view);
    }

    void insert_view(SessionItem* parent, TagRow tagrow)
    {
        auto child = parent->getItem(tagrow.tag, tagrow.row);
        auto children = children_strategy->children(parent);
        auto index = Utils::IndexOfItem(children, child);
        if (index == -1)
            return;

        auto pos = item_to_view.find(parent);
        if (pos == item_to_view.end())
            return;

        auto parent_view = pos->second;

        auto row = row_strategy->constructRefRow(child);
        if (!row.empty()) {
            auto next_parent = row.at(0).get();
            view_model->insertRow(parent_view, index, std::move(row));
            item_to_view[child] = next_parent;
            parent_view = next_parent; // labelItem
            iterate(child, parent_view);
        }
    }

    void setSessionModel(SessionModel* model)
    {
        session_model = model;

        auto on_data_change = [this](SessionItem* item, int role) {
            controller->onDataChange(item, role);
        };
        session_model->mapper()->setOnDataChange(on_data_change, controller);

        auto on_item_inserted = [this](SessionItem* item, TagRow tagrow) {
            controller->onItemInserted(item, tagrow);
        };
        session_model->mapper()->setOnItemInserted(on_item_inserted, controller);

        auto on_item_removed = [this](SessionItem* item, TagRow tagrow) {
            controller->onItemRemoved(item, tagrow);
        };
        session_model->mapper()->setOnItemRemoved(on_item_removed, controller);

        auto on_about_to_remove = [this](SessionItem* item, TagRow tagrow) {
            controller->onAboutToRemoveItem(item, tagrow);
        };
        session_model->mapper()->setOnAboutToRemoveItem(on_about_to_remove, controller);

        auto on_model_destroyed = [this](SessionModel*) {
            session_model = nullptr;
            view_model->setRootViewItem(std::make_unique<RootViewItem>(nullptr));
        };
        session_model->mapper()->setOnModelDestroyed(on_model_destroyed, controller);

        auto on_model_reset = [this](SessionModel*) {
            view_model->setRootViewItem(std::make_unique<RootViewItem>(session_model->rootItem()));
        };
        session_model->mapper()->setOnModelReset(on_model_reset, controller);
    }

    std::vector<ViewItem*> findViews(const SessionItem* item) const
    {
        if (item == view_model->rootItem()->item())
            return {view_model->rootItem()};

        std::vector<ViewItem*> result;
        auto on_index = [&](const QModelIndex& index) {
            auto view_item = view_model->itemFromIndex(index);
            if (view_item->item() == item)
                result.push_back(view_item);
        };
        Utils::iterate_model(view_model, QModelIndex(), on_index);
        return result;
    }
};

ViewModelController::ViewModelController(SessionModel* session_model, ViewModelBase* view_model)
    : p_impl(std::make_unique<RefViewModelControllerImpl>(this, session_model, view_model))
{
}

ViewModelController::~ViewModelController()
{
    if (p_impl->session_model)
        p_impl->session_model->mapper()->unsubscribe(this);
}

void ViewModelController::setChildrenStrategy(
    std::unique_ptr<ChildrenStrategyInterface> children_strategy)
{
    p_impl->children_strategy = std::move(children_strategy);
}

void ViewModelController::setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy)
{
    p_impl->row_strategy = std::move(row_strategy);
}

//! Returns SessionModel handled by this controller.

SessionModel* ViewModelController::sessionModel() const
{
    return p_impl->session_model;
}

void ViewModelController::setRootSessionItem(SessionItem* item)
{
    p_impl->view_model->setRootViewItem(std::make_unique<RootViewItem>(item));
    p_impl->init_view_model();
}

SessionItem* ViewModelController::rootSessionItem() const
{
    return p_impl->view_model->rootItem()->item();
}

//! Returns all ViewItem's displaying given SessionItem.

std::vector<ViewItem*> ViewModelController::findViews(const SessionItem* item) const
{
    return p_impl->findViews(item);
}

QStringList ViewModelController::horizontalHeaderLabels() const
{
    return p_impl->row_strategy->horizontalHeaderLabels();
}

void ViewModelController::onDataChange(SessionItem* item, int role)
{
    for (auto view : findViews(item)) {
        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = p_impl->view_model->indexFromItem(view);
            p_impl->view_model->dataChanged(index, index, Utils::item_role_to_qt(role));
        }
    }
}

void ViewModelController::onItemInserted(SessionItem* parent, TagRow tagrow)
{
    p_impl->insert_view(parent, tagrow);
}

void ViewModelController::onItemRemoved(SessionItem*, TagRow) {}

void ViewModelController::onAboutToRemoveItem(SessionItem* parent, TagRow tagrow)
{
    p_impl->remove_row_of_views(parent->getItem(tagrow.tag, tagrow.row));
}

void ViewModelController::update_branch(const SessionItem* item)
{
    auto views = findViews(item);
    if (views.empty())
        return;

    for (auto view : views)
        p_impl->remove_children_of_view(view);

    p_impl->iterate(item, views.at(0));
}
