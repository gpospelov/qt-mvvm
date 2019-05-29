// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodelcontroller.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "childrenstrategyinterface.h"
#include "rowconstructorinterface.h"
#include "abstractviewmodel.h"

using namespace ModelView;

class ViewModelController::ViewModelControllerPrivate
{
public:
    ViewModelControllerPrivate(AbstractViewModel* view_model) : m_view_model(view_model), m_root_item(nullptr), m_session_model(nullptr) {}
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

std::vector<SessionItem*> ViewModelController::item_children(const SessionItem* item) const
{
    return p_impl->m_children_strategy->children(item);
}

void ViewModelController::setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy)
{
    p_impl->m_children_strategy = std::move(children_strategy);
}

void ViewModelController::setRowConstructor(std::unique_ptr<RowConstructorInterface> row_constructor)
{
    p_impl->m_row_constructor = std::move(row_constructor);
}

QList<QStandardItem*> ViewModelController::constructRow(SessionItem* item)
{
    return p_impl->m_row_constructor->constructRow(item);
}

void ViewModelController::update_layout()
{
    p_impl->m_view_model->setColumnCount(p_impl->m_row_constructor->columnCount());
    p_impl->m_view_model->setHorizontalHeaderLabels(p_impl->m_row_constructor->horizontalHeaderLabels());
}

ViewModelController::~ViewModelController() = default;
