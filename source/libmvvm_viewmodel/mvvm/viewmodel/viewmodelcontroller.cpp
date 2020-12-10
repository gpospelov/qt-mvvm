// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <map>
#include <mvvm/interfaces/childrenstrategyinterface.h>
#include <mvvm/interfaces/rowstrategyinterface.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/utils/containerutils.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <mvvm/viewmodel/viewmodelbase.h>
#include <mvvm/viewmodel/viewmodelcontroller.h>
#include <mvvm/viewmodel/viewmodelutils.h>
#include <stdexcept>

using namespace ModelView;

namespace
{

//! Returns true if given SessionItem role is valid for view
bool isValidItemRole(const ViewItem* view, int item_role)
{
    if (view->item_role() == item_role)
        return true;

    if (item_role == ItemDataRole::APPEARANCE || item_role == ItemDataRole::TOOLTIP)
        return true;
    return false;
}

} // namespace

struct ViewModelController::ViewModelControllerImpl {
    ViewModelController* controller;
    ViewModelBase* view_model{nullptr};
    std::unique_ptr<ChildrenStrategyInterface> children_strategy;
    std::unique_ptr<RowStrategyInterface> row_strategy;
    std::map<SessionItem*, ViewItem*> item_to_view; //! correspondence of item and its view
    Path root_item_path;

    ViewModelControllerImpl(ViewModelController* controller, ViewModelBase* view_model)
        : controller(controller), view_model(view_model)
    {
    }

    void check_initialization()
    {
        const std::string msg("Error in ViewModelController: ");
        if (!view_model)
            throw std::runtime_error(msg + "ViewModel is not defined");

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
            auto row = row_strategy->constructRow(child);
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

    void insert_view(SessionItem* parent, const TagRow& tagrow)
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

        auto row = row_strategy->constructRow(child);
        if (!row.empty()) {
            auto next_parent = row.at(0).get();
            view_model->insertRow(parent_view, index, std::move(row));
            item_to_view[child] = next_parent;
            parent_view = next_parent; // labelItem
            iterate(child, parent_view);
        }
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

    void setRootSessionItemIntern(SessionItem* item)
    {
        root_item_path = controller->model()->pathFromItem(item);
        view_model->setRootViewItem(std::make_unique<RootViewItem>(item));
        init_view_model();
    }
};

ViewModelController::ViewModelController(SessionModel* session_model, ViewModelBase* view_model)
    : ModelListener(session_model)
    , p_impl(std::make_unique<ViewModelControllerImpl>(this, view_model))
{
    auto on_data_change = [this](SessionItem* item, int role) { onDataChange(item, role); };
    setOnDataChange(on_data_change);

    auto on_item_inserted = [this](SessionItem* item, TagRow tagrow) {
        onItemInserted(item, std::move(tagrow));
    };
    setOnItemInserted(on_item_inserted);

    auto on_item_removed = [this](SessionItem* item, TagRow tagrow) {
        onItemRemoved(item, std::move(tagrow));
    };
    setOnItemRemoved(on_item_removed);

    auto on_about_to_remove = [this](SessionItem* item, TagRow tagrow) {
        onAboutToRemoveItem(item, std::move(tagrow));
    };
    setOnAboutToRemoveItem(on_about_to_remove);

    auto on_model_destroyed = [this](auto) {
        p_impl->view_model->setRootViewItem(std::make_unique<RootViewItem>(nullptr));
    };
    setOnModelDestroyed(on_model_destroyed);

    auto on_model_reset = [this](auto) {
        auto root_item = model()->itemFromPath(p_impl->root_item_path);
        p_impl->setRootSessionItemIntern(root_item ? root_item : model()->rootItem());
        p_impl->view_model->endResetModel();
    };
    setOnModelReset(on_model_reset);

    auto on_model_about_to_be_reset = [this](auto) { p_impl->view_model->beginResetModel(); };
    setOnModelAboutToBeReset(on_model_about_to_be_reset);
}

void ViewModelController::setViewModel(ViewModelBase* view_model)
{
    p_impl->view_model = view_model;
}

ViewModelController::~ViewModelController() = default;

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
    return model();
}

void ViewModelController::setRootSessionItem(SessionItem* item)
{
    if (!item)
        throw std::runtime_error(
            "Error in ViewModelController: atttemp to set nulptr as root item");

    if (item->model() != model())
        throw std::runtime_error(
            "Error in ViewModelController: atttemp to use item from alien model as new root.");

    p_impl->view_model->beginResetModel();
    p_impl->setRootSessionItemIntern(item);
    p_impl->view_model->endResetModel();
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
            p_impl->view_model->dataChanged(index, index, Utils::ItemRoleToQtRole(role));
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
    auto item_to_remove = parent->getItem(tagrow.tag, tagrow.row);
    if (item_to_remove == rootSessionItem()
        || Utils::IsItemAncestor(rootSessionItem(), item_to_remove)) {
        // special case when user removes SessionItem which is one of ancestors of our root item
        // or root item iteslf
        p_impl->view_model->beginResetModel();
        p_impl->view_model->setRootViewItem(std::make_unique<RootViewItem>(nullptr));
        p_impl->item_to_view.clear();
        p_impl->root_item_path = {};
        p_impl->view_model->endResetModel();
    } else {
        p_impl->remove_row_of_views(item_to_remove);
    }
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
