// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "abstractviewmodel.h"
#include "childrenstrategyinterface.h"
#include "modelmapper.h"
#include "rowconstructorinterface.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewitems.h"
#include "viewmodelcontroller.h"
#include "viewmodelutils.h"
#include <utility>

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

AbstractViewModel::AbstractViewModel(QObject* parent)
    : QStandardItemModel(parent),
      m_controller(std::make_unique<ViewModelController>(this))
{
    setItemPrototype(new ViewEmptyItem);
}

AbstractViewModel::~AbstractViewModel()
{
}

void AbstractViewModel::setSessionModel(SessionModel* model)
{
    m_controller->setSessionModel(model);
}


//! Returns QStandardItem associated with top level item (rootSessionItem).

QStandardItem* AbstractViewModel::rootViewItem() const
{
    return invisibleRootItem();
}

//! Returns vector of standard views used to display given SessionItem.

std::vector<QStandardItem*> AbstractViewModel::findStandardViews(const SessionItem* item) const
{
    if (item == m_controller->rootSessionItem())
        return {rootViewItem()};

    std::vector<QStandardItem*> result;
    for (auto view : findViews(item))
        result.push_back(view);

    return result;
}

std::vector<ViewItem*> AbstractViewModel::findViews(const SessionItem* item) const
{
    return Utils::findViews(this, item, QModelIndex());
}

//! Returns SessionItem corresponding to givem QModelIndex.

SessionItem* AbstractViewModel::sessionItemFromIndex(const QModelIndex& index) const
{
    SessionItem* result(nullptr);
    if (!m_controller->sessionModel())
        return result;

    if (index.isValid()) {
        if (auto viewItem = dynamic_cast<ViewItem*>(itemFromIndex(index)))
            result = viewItem->item();
    } else {
        result = m_controller->rootSessionItem();
    }

    return result;
}

//! Returns list of QModelIndex'es related to given SessionItem.

QModelIndexList AbstractViewModel::indexOfSessionItem(const SessionItem* item) const
{
    QModelIndexList result;
    for (auto view : findStandardViews(item))
        result.push_back(indexFromItem(view));
    return result;
}

void AbstractViewModel::setRootSessionItem(SessionItem* item)
{
    m_controller->setRootSessionItem(item);
}

//! Generates necessary notifications on SessionItem's data change.

void AbstractViewModel::onDataChange(SessionItem* item, int role)
{
    for (auto view : findViews(item)) {

        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = indexFromItem(view);
            dataChanged(index, index, Utils::item_role_to_qt(role));
        }
    }
}

//! Insert views (QStandardItem's) when given SessionItem gets its new row.

void AbstractViewModel::onRowInserted(SessionItem* parent, std::string, int)
{
    generate_children_views(parent);
}

//! Removes views (QStandardItem's) corresponding to given SessionItem and its row.

void AbstractViewModel::onRowRemoved(SessionItem* parent, std::string, int)
{
    generate_children_views(parent);
}

void AbstractViewModel::setRowConstructor(std::unique_ptr<RowConstructorInterface> row_constructor)
{
    m_controller->setRowConstructor(std::move(row_constructor));
}

void AbstractViewModel::setChildrenStrategy(
    std::unique_ptr<ChildrenStrategyInterface> children_strategy)
{
    m_controller->setChildrenStrategy(std::move(children_strategy));
}

//! Regenerate all views of given parent.

void AbstractViewModel::generate_children_views(SessionItem* parent)
{
    auto views = findStandardViews(parent);
    for (auto view : views)
        view->removeRows(0, view->rowCount());

    if (views.size())
        m_controller->iterate(parent, views.at(0));
}
