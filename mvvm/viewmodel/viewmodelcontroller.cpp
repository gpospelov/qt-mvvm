// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodelcontroller.h"
#include "abstractviewmodel.h"
#include "childrenstrategyinterface.h"
#include "rowconstructorinterface.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "modelmapper.h"
#include "viewitem.h"
#include "viewmodelutils.h"

namespace
{

//! Returns true if given SessionItem role is valid for view
bool isValidItemRole(const ModelView::ViewItem* view, int item_role)
{
    if (view->item_role() == item_role)
        return true;

    if (item_role == ModelView::ItemDataRole::APPEARANCE)
        return true;
    return false;
}
} // namespace

using namespace ModelView;

class ViewModelController::ViewModelControllerPrivate
{
public:
    ViewModelControllerPrivate(AbstractViewModel* view_model)
        : m_view_model(view_model), m_root_item(nullptr), m_session_model(nullptr)
    {
    }

    QList<QStandardItem*> constructRow(SessionItem* item)
    {
        return m_row_constructor->constructRow(item);
    }

    std::vector<SessionItem*> item_children(const SessionItem* item) const
    {
        return m_children_strategy->children(item);
    }

    void reset_view_model()
    {
        m_view_model->clear();
        update_layout();
    }

    void update_layout()
    {
        m_view_model->setColumnCount(m_row_constructor->columnCount());
        m_view_model->setHorizontalHeaderLabels(
        m_row_constructor->horizontalHeaderLabels());
    }

    AbstractViewModel* m_view_model;
    SessionItem* m_root_item;
    SessionModel* m_session_model;
    std::unique_ptr<ChildrenStrategyInterface> m_children_strategy;
    std::unique_ptr<RowConstructorInterface> m_row_constructor;
};

ViewModelController::ViewModelController(AbstractViewModel* view_model)
    : p_impl(std::make_unique<ViewModelControllerPrivate>(view_model))
{
}

ViewModelController::~ViewModelController()
{
    if (sessionModel())
        sessionModel()->mapper()->unsubscribe(this);
}

void ViewModelController::setSessionModel(SessionModel* model)
{
    if (sessionModel())
        sessionModel()->mapper()->unsubscribe(this);

    p_impl->m_session_model = model;

    if (sessionModel()) {
        auto on_data_change = [this](SessionItem* item, int role) { onDataChange(item, role); };
        sessionModel()->mapper()->setOnDataChange(on_data_change, this);

        auto on_row_inserted = [this](SessionItem* item, std::string tag, int row) {
            onRowInserted(item, tag, row);
        };
        sessionModel()->mapper()->setOnRowInserted(on_row_inserted, this);

        auto on_row_removed = [this](SessionItem* item, std::string tag, int row) {
            onRowRemoved(item, tag, row);
        };
        sessionModel()->mapper()->setOnRowRemoved(on_row_removed, this);

        auto on_model_destroyed = [this](SessionModel*) {
            p_impl->m_session_model = nullptr;
            p_impl->m_view_model->clear();
        };
        sessionModel()->mapper()->setOnModelDestroyed(on_model_destroyed, this);

        auto on_model_reset = [this](SessionModel*) {
            setRootSessionItem(nullptr);
            reset_view_model();
        };
        sessionModel()->mapper()->setOnModelReset(on_model_reset, this);

        init_view_model();
    }

}

void ViewModelController::setChildrenStrategy(
    std::unique_ptr<ChildrenStrategyInterface> children_strategy)
{
    p_impl->m_children_strategy = std::move(children_strategy);
}

void ViewModelController::setRowConstructor(
    std::unique_ptr<RowConstructorInterface> row_constructor)
{
    p_impl->m_row_constructor = std::move(row_constructor);
}

void ViewModelController::reset_view_model()
{
    p_impl->reset_view_model();
}

void ViewModelController::iterate(const SessionItem* item, QStandardItem* parent)
{
    QStandardItem* origParent(parent);
    for (auto child : p_impl->item_children(item)) {

        auto row = p_impl->constructRow(child);
        parent->appendRow(row);

        if (row.size())
            parent = row.at(0); // labelItem

        iterate(child, parent);
        parent = origParent;
    }
}

void ViewModelController::init_view_model()
{
    if (!p_impl->m_row_constructor)
        throw std::runtime_error("AbstractViewModel::init_view_model() -> Error. Row constructor "
                                     "is not initialized.");

    if (!p_impl->m_children_strategy)
        throw std::runtime_error("AbstractViewModel::init_view_model() -> Error. Children strategy "
                                     "is not initialized.");

    reset_view_model();
    iterate(rootSessionItem(), p_impl->m_view_model->rootViewItem());
}

void ViewModelController::setRootSessionItem(SessionItem* item)
{
    if (item && item->model() != sessionModel())
        throw std::runtime_error(
            "ViewModel::setRootSessionItem()->Error. Item doesn't belong to a model.");

    p_impl->m_root_item = item;
    init_view_model();
}

//! Returns root item of the model. Can be different from model's root item when the intention is
//! to show only part of the model.

SessionItem* ViewModelController::rootSessionItem() const
{
    return p_impl->m_root_item ? p_impl->m_root_item : sessionModel()->rootItem();
}

SessionModel* ViewModelController::sessionModel()
{
    return p_impl->m_session_model;
}

const SessionModel* ViewModelController::sessionModel() const
{
    return p_impl->m_session_model;
}

void ViewModelController::generate_children_views(SessionItem* parent)
{
    auto views = p_impl->m_view_model->findStandardViews(parent);
    for (auto view : views)
        view->removeRows(0, view->rowCount());

    if (views.size())
        iterate(parent, views.at(0));
}

//! Generates necessary notifications on SessionItem's data change.

void ViewModelController::onDataChange(SessionItem* item, int role)
{
    for (auto view : p_impl->m_view_model->findViews(item)) {
        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = p_impl->m_view_model->indexFromItem(view);
            p_impl->m_view_model->dataChanged(index, index, Utils::item_role_to_qt(role));
        }
    }

}

//! Rebuild view model branch on session model change.

void ViewModelController::onRowInserted(SessionItem* parent, std::string, int)
{
    generate_children_views(parent);
}

//! Rebuild view model branch on session model change.

void ViewModelController::onRowRemoved(SessionItem* parent, std::string, int)
{
    generate_children_views(parent);
}

