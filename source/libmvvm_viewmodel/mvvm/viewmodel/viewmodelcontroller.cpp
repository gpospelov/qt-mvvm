// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/viewmodelcontroller.h"
#include "mvvm/interfaces/childrenstrategyinterface.h"
#include "mvvm/interfaces/rowstrategyinterface.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/model/path.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/utils/containerutils.h"
#include "mvvm/viewmodel/standardviewitems.h"
#include "mvvm/viewmodel/viewmodelbase.h"
#include "mvvm/viewmodel/viewmodelutils.h"
#include <map>
#include <stdexcept>

using namespace ModelView;

namespace {

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
    ViewModelController* m_self;
    ViewModelBase* m_viewModel{nullptr};
    std::unique_ptr<ChildrenStrategyInterface> m_childrenStrategy;
    std::unique_ptr<RowStrategyInterface> m_rowStrategy;
    std::map<SessionItem*, ViewItem*> m_itemToVview; //! correspondence of item and its view
    Path m_rootItemPath;

    ViewModelControllerImpl(ViewModelController* controller, ViewModelBase* view_model)
        : m_self(controller), m_viewModel(view_model)
    {
    }

    void check_initialization()
    {
        const std::string msg("Error in ViewModelController: ");
        if (!m_viewModel)
            throw std::runtime_error(msg + "ViewModel is not defined");

        if (!m_rowStrategy)
            throw std::runtime_error(msg + "RowStrategy is not defined");

        if (!m_childrenStrategy)
            throw std::runtime_error(msg + "Children is not defined");
    }

    void init_view_model()
    {
        check_initialization();
        m_itemToVview.clear();
        m_itemToVview[m_self->rootSessionItem()] = m_viewModel->rootItem();
        iterate(m_self->rootSessionItem(), m_viewModel->rootItem());
    }

    void iterate(const SessionItem* item, ViewItem* parent)
    {
        ViewItem* origParent(parent);
        for (auto child : m_childrenStrategy->children(item)) {
            auto row = m_rowStrategy->constructRow(child);
            if (!row.empty()) {
                auto next_parent = row.at(0).get();
                m_viewModel->appendRow(parent, std::move(row));
                m_itemToVview[child] = next_parent;
                parent = next_parent; // labelItem
                iterate(child, parent);
            }
            parent = origParent;
        }
    }

    //! Remove row of ViewItem's corresponding to given item.

    void remove_row_of_views(SessionItem* item)
    {
        auto pos = m_itemToVview.find(item);
        if (pos != m_itemToVview.end()) {
            auto view = pos->second;
            m_viewModel->removeRow(view->parent(), view->row());
            m_itemToVview.erase(pos);
        }
    }

    void remove_children_of_view(ViewItem* view)
    {
        for (auto child : view->children()) {
            auto pos = std::find_if(m_itemToVview.begin(), m_itemToVview.end(),
                                    [child](const auto& it) { return it.second == child; });
            if (pos != m_itemToVview.end())
                m_itemToVview.erase(pos);
        }

        m_viewModel->clearRows(view);
    }

    void insert_view(SessionItem* parent, const TagRow& tagrow)
    {
        auto child = parent->getItem(tagrow.tag, tagrow.row);
        auto children = m_childrenStrategy->children(parent);
        auto index = Utils::IndexOfItem(children, child);
        if (index == -1)
            return;

        auto pos = m_itemToVview.find(parent);
        if (pos == m_itemToVview.end())
            return;

        auto parent_view = pos->second;

        auto row = m_rowStrategy->constructRow(child);
        if (!row.empty()) {
            auto next_parent = row.at(0).get();
            m_viewModel->insertRow(parent_view, index, std::move(row));
            m_itemToVview[child] = next_parent;
            parent_view = next_parent; // labelItem
            iterate(child, parent_view);
        }
    }

    std::vector<ViewItem*> findViews(const SessionItem* item) const
    {
        if (item == m_viewModel->rootItem()->item())
            return {m_viewModel->rootItem()};

        std::vector<ViewItem*> result;
        auto on_index = [&](const QModelIndex& index) {
            auto view_item = m_viewModel->itemFromIndex(index);
            if (view_item->item() == item)
                result.push_back(view_item);
        };
        Utils::iterate_model(m_viewModel, QModelIndex(), on_index);
        return result;
    }

    void setRootSessionItemIntern(SessionItem* item)
    {
        m_rootItemPath = Utils::PathFromItem(item);
        m_viewModel->setRootViewItem(std::make_unique<RootViewItem>(item));
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
        p_impl->m_viewModel->setRootViewItem(std::make_unique<RootViewItem>(nullptr));
    };
    setOnModelDestroyed(on_model_destroyed);

    auto on_model_reset = [this](auto) {
        auto root_item = Utils::ItemFromPath(*model(), p_impl->m_rootItemPath);
        p_impl->setRootSessionItemIntern(root_item ? root_item : model()->rootItem());
        p_impl->m_viewModel->endResetModel();
        p_impl->init_view_model();
    };
    setOnModelReset(on_model_reset);

    auto on_model_about_to_be_reset = [this](auto) { p_impl->m_viewModel->beginResetModel(); };
    setOnModelAboutToBeReset(on_model_about_to_be_reset);
}

void ViewModelController::setViewModel(ViewModelBase* view_model)
{
    p_impl->m_viewModel = view_model;
}

ViewModelController::~ViewModelController() = default;

void ViewModelController::setChildrenStrategy(
    std::unique_ptr<ChildrenStrategyInterface> children_strategy)
{
    p_impl->m_childrenStrategy = std::move(children_strategy);
}

void ViewModelController::setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy)
{
    p_impl->m_rowStrategy = std::move(row_strategy);
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

    p_impl->m_viewModel->beginResetModel();
    p_impl->setRootSessionItemIntern(item);
    p_impl->m_viewModel->endResetModel();
    p_impl->init_view_model();
}

SessionItem* ViewModelController::rootSessionItem() const
{
    return p_impl->m_viewModel->rootItem()->item();
}

//! Returns all ViewItem's displaying given SessionItem.

std::vector<ViewItem*> ViewModelController::findViews(const SessionItem* item) const
{
    return p_impl->findViews(item);
}

QStringList ViewModelController::horizontalHeaderLabels() const
{
    return p_impl->m_rowStrategy->horizontalHeaderLabels();
}

void ViewModelController::onDataChange(SessionItem* item, int role)
{
    for (auto view : findViews(item)) {
        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = p_impl->m_viewModel->indexFromItem(view);
            p_impl->m_viewModel->dataChanged(index, index, Utils::ItemRoleToQtRole(role));
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
        p_impl->m_viewModel->beginResetModel();
        p_impl->m_viewModel->setRootViewItem(std::make_unique<RootViewItem>(nullptr));
        p_impl->m_itemToVview.clear();
        p_impl->m_rootItemPath = {};
        p_impl->m_viewModel->endResetModel();
    }
    else {
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
