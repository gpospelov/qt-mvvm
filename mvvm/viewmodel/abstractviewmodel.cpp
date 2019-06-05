// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "abstractviewmodel.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewitems.h"
#include "abstractviewmodelcontroller.h"
#include "viewmodelutils.h"

using namespace ModelView;

AbstractViewModel::AbstractViewModel(std::unique_ptr<AbstractViewModelController> controller, QObject* parent)
    : QStandardItemModel(parent),
      m_controller(std::move(controller))
{
    m_controller->setViewModel(this);
    setItemPrototype(new ViewEmptyItem);
}

AbstractViewModel::~AbstractViewModel() = default;

void AbstractViewModel::setSessionModel(SessionModel* model)
{
    m_controller->setSessionModel(model);
}

void AbstractViewModel::setRootSessionItem(SessionItem* item)
{
    m_controller->setRootSessionItem(item);
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

//! Returns SessionItem corresponding to given QModelIndex.

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
