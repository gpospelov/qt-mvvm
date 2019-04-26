// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "abstractviewmodel.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewitems.h"
#include "viewmodelutils.h"

using namespace ModelView;

AbstractViewModel::AbstractViewModel(QObject* parent)
    : QStandardItemModel(parent), m_sessionModel(nullptr), m_rootItem(nullptr)
{
}

AbstractViewModel::~AbstractViewModel()
{
    if (m_sessionModel)
        m_sessionModel->mapper()->unsubscribe(this);
}

void AbstractViewModel::setSessionModel(SessionModel* model)
{
    if (m_sessionModel)
        m_sessionModel->mapper()->unsubscribe(this);

    m_sessionModel = model;

    if (m_sessionModel) {
        auto on_data_change = [this](SessionItem* item, int role) { onDataChange(item, role); };
        m_sessionModel->mapper()->setOnDataChange(on_data_change, this);

        auto on_row_inserted = [this](SessionItem* item, std::string tag, int row) {
            onRowInserted(item, tag, row);
        };
        m_sessionModel->mapper()->setOnRowInserted(on_row_inserted, this);

        auto on_row_removed = [this](SessionItem* item, std::string tag, int row) {
            onRowRemoved(item, tag, row);
        };
        m_sessionModel->mapper()->setOnRowRemoved(on_row_removed, this);

        auto on_model_destroyed = [this](SessionModel*) { m_sessionModel = nullptr; clear();};
        m_sessionModel->mapper()->setOnModelDestroyed(on_model_destroyed, this);

        m_rootItem = model->rootItem();

        init_view_model();
    }
}

//! Returns root item of the model. Can be different from model's root item when the intention is
//! to show only part of the model.

SessionItem* AbstractViewModel::rootSessionItem() const
{
    return m_rootItem;
}

//! Returns QStandardItem associated with top level item (rootSessionItem).

QStandardItem* AbstractViewModel::rootStandardItem() const
{
    return invisibleRootItem();
}

//! Returns vector of standard views used to display given SessionItem.

std::vector<QStandardItem*> AbstractViewModel::findStandardViews(const SessionItem* item) const
{
    if (item == rootSessionItem())
        return {rootStandardItem()};

    std::vector<QStandardItem*> result;
    for (auto view : findViews(item))
        result.push_back(view);

    return result;
}

std::vector<ViewItem*> AbstractViewModel::findViews(const SessionItem* item) const
{
    return Utils::findViews(this, QModelIndex(), item);
}

//! Returns SessionItem corresponding to givem QModelIndex.

SessionItem* AbstractViewModel::sessionItemFromIndex(const QModelIndex& index) const
{
    SessionItem* result(nullptr);
    if (!m_sessionModel)
        return result;

    if (index.isValid()) {
        if (auto viewItem = dynamic_cast<ViewItem*>(itemFromIndex(index)))
            result = viewItem->item();
    } else {
        result = rootSessionItem();
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
    if (item->model() != m_sessionModel)
        throw std::runtime_error(
            "ViewModel::setRootSessionItem()->Error. Item doesn't belong to a model.");

    m_rootItem = item;
    init_view_model();
}

void AbstractViewModel::onDataChange(SessionItem* item, int role)
{
    Q_UNUSED(item)
    Q_UNUSED(role)
}

void AbstractViewModel::onRowInserted(SessionItem* parent, std::string tag, int row)
{
    Q_UNUSED(parent)
    Q_UNUSED(tag)
    Q_UNUSED(row)
}

void AbstractViewModel::onRowRemoved(SessionItem* parent, std::string tag, int row)
{
    Q_UNUSED(parent)
    Q_UNUSED(tag)
    Q_UNUSED(row)
}
