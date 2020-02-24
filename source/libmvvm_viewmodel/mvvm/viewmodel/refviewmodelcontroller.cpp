// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <map>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/modelmapper.h>
#include <mvvm/viewmodel/childrenstrategyinterface.h>
#include <mvvm/viewmodel/refviewitems.h>
#include <mvvm/viewmodel/refviewmodel.h>
#include <mvvm/viewmodel/refviewmodelcontroller.h>
#include <mvvm/viewmodel/rowstrategyinterface.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

namespace
{

//! Return vector of underlying SessionItems for given view item at given row.

std::vector<SessionItem*> current_items_at_row(RefViewItem* parent, int row)
{
    std::vector<SessionItem*> result;
    if (row < parent->rowCount())
        for (int column = 0; column < parent->columnCount(); ++column)
            result.push_back(parent->child(row, column)->item());
    return result;
}

//! Return vector of underlying SessionItems from given vector of view items.

std::vector<SessionItem*>
underlying_items(const std::vector<std::unique_ptr<RefViewItem>>& view_items)
{
    std::vector<SessionItem*> result;
    std::transform(view_items.begin(), view_items.end(), std::back_inserter(result),
                   [](const auto& x) { return x.get()->item(); });
    return result;
}

//! Returns true if a row with same underlying SessionItem's was already inserted to the parent.

bool row_was_already_inserted(RefViewItem* parent, int row,
                              const std::vector<std::unique_ptr<RefViewItem>>& candidates)
{
    return current_items_at_row(parent, row) == underlying_items(candidates);
}

//! Returns true if given SessionItem role is valid for view
bool isValidItemRole(const RefViewItem* view, int item_role)
{
    if (view->item_role() == item_role)
        return true;

    if (item_role == ModelView::ItemDataRole::APPEARANCE)
        return true;
    return false;
}

} // namespace

struct RefViewModelController::RefViewModelControllerImpl {
    RefViewModelController* controller;
    SessionModel* session_model{nullptr};
    RefViewModel* view_model{nullptr};
    std::unique_ptr<ChildrenStrategyInterface> children_strategy;
    std::unique_ptr<RowStrategyInterface> row_strategy;
    std::map<SessionItem*, RefViewItem*> item_to_view; //! correspondence of item and its view

    RefViewModelControllerImpl(RefViewModelController* controller, SessionModel* session_model,
                               RefViewModel* view_model)
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
        iterate_insert(controller->rootSessionItem(), view_model->rootItem());
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

    //! Populates ViewModel with content of SessionModel. Triggered by insertEvent in SessionModel.
    //! a) Iterates over all SessionItem's following children strategy.
    //! b) Constructs corresponding rows of ViewItems' following row strategy
    //! c) Adds them to parent ViewItem, if they have not been added yet.
    //! c) Or just skips row of ViewItem's and jumps further.

    void iterate_insert(const SessionItem* item, RefViewItem* parent)
    {
        RefViewItem* origParent(parent);
        int nrow(0);
        for (auto child : children_strategy->children(item)) {
            auto row = row_strategy->constructRefRow(child);
            if (!row.empty()) {
                RefViewItem* next_parent{nullptr};
                if (row_was_already_inserted(parent, nrow, row)) {
                    next_parent = parent->child(nrow, 0);
                } else {
                    next_parent = row.at(0).get();
                    item_to_view[child] = next_parent;
                    view_model->insertRow(parent, nrow, std::move(row));
                }
                parent = next_parent;
                iterate_insert(child, parent);
            }
            parent = origParent;
            ++nrow;
        }
    }

    void iterate_remove(const SessionItem* item, RefViewItem* parent)
    {
        RefViewItem* origParent(parent);
        int nrow(0);

        auto children = children_strategy->children(item);
        if (children.empty() && view_model->rowCount(view_model->indexFromItem(parent)) == 1)
            view_model->removeRow(parent, 0);

        for (auto child : children) {
            auto row = row_strategy->constructRefRow(child);
            if (!row.empty()) {
                if (row_was_already_inserted(parent, nrow, row))
                    continue;

                view_model->removeRow(parent, nrow);
                //                auto next_parent = row.at(0).get();
                //                view_model->insertRow(parent, nrow, std::move(row));
                //                parent = next_parent; // labelItem
                //                iterate(child, parent);
            }
            parent = origParent;
            ++nrow;
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
            view_model->setRootViewItem(std::make_unique<RefRootViewItem>(nullptr));
        };
        session_model->mapper()->setOnModelDestroyed(on_model_destroyed, controller);

        auto on_model_reset = [this](SessionModel*) {
            view_model->setRootViewItem(
                std::make_unique<RefRootViewItem>(session_model->rootItem()));
        };
        session_model->mapper()->setOnModelReset(on_model_reset, controller);
    }

    std::vector<RefViewItem*> findViews(const SessionItem* item) const
    {
        if (item == session_model->rootItem())
            return {view_model->rootItem()};

        std::vector<RefViewItem*> result;
        auto on_index = [&](const QModelIndex& index) {
            auto view_item = view_model->itemFromIndex(index);
            if (view_item->item() == item)
                result.push_back(view_item);
        };
        Utils::iterate_model(view_model, QModelIndex(), on_index);
        return result;
    }
};

RefViewModelController::RefViewModelController(SessionModel* session_model,
                                               RefViewModel* view_model)
    : p_impl(std::make_unique<RefViewModelControllerImpl>(this, session_model, view_model))
{
}

RefViewModelController::~RefViewModelController()
{
    if (p_impl->session_model)
        p_impl->session_model->mapper()->unsubscribe(this);
}

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
    p_impl->init_view_model();
}

SessionItem* RefViewModelController::rootSessionItem() const
{
    return p_impl->view_model->rootItem()->item();
}

//! Returns all ViewItem's displaying given SessionItem.

std::vector<RefViewItem*> RefViewModelController::findViews(const SessionItem* item) const
{
    return p_impl->findViews(item);
}

void RefViewModelController::onDataChange(SessionItem* item, int role)
{
    for (auto view : findViews(item)) {
        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = p_impl->view_model->indexFromItem(view);
            p_impl->view_model->dataChanged(index, index, Utils::item_role_to_qt(role));
        }
    }
}

void RefViewModelController::onItemInserted(SessionItem*, TagRow)
{
    p_impl->iterate_insert(rootSessionItem(), p_impl->view_model->rootItem());
}

void RefViewModelController::onItemRemoved(SessionItem*, TagRow)
{
    //    p_impl->iterate_remove(rootSessionItem(), p_impl->view_model->rootItem());
}

void RefViewModelController::onAboutToRemoveItem(SessionItem* parent, TagRow tagrow)
{
    p_impl->remove_row_of_views(parent->getItem(tagrow.tag, tagrow.row));
}
