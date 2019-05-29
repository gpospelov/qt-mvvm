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
    p_impl->m_view_model->clear();
    update_layout();
}

void ViewModelController::update_layout()
{
    p_impl->m_view_model->setColumnCount(p_impl->m_row_constructor->columnCount());
    p_impl->m_view_model->setHorizontalHeaderLabels(
        p_impl->m_row_constructor->horizontalHeaderLabels());
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

ViewModelController::~ViewModelController() = default;
