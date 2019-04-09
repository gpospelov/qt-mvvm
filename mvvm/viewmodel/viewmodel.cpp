// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodel.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewitems.h"
#include "viewmodelutils.h"

using namespace ModelView;

ViewModel::ViewModel(QObject* parent)
    : QStandardItemModel(parent), m_sessionModel(nullptr), m_rootItem(nullptr)
{
}

ViewModel::~ViewModel() = default;

void ViewModel::setSessionModel(SessionModel* model)
{
    if (m_sessionModel) {
        m_sessionModel->mapper()->unsubscribe(this);
    }

    m_sessionModel = model;

    if (m_sessionModel) {
        m_sessionModel->mapper()->setOnDataChange(
            [this](ModelView::SessionItem* item, int role) { onDataChange(item, role); }, this);

        m_sessionModel->mapper()->setOnRowInserted(
            [this](ModelView::SessionItem* item, std::string tag, int row) {
                onRowInserted(item, tag, row);
            },
            this);

        m_sessionModel->mapper()->setOnRowRemoved([this](ModelView::SessionItem* item,
                                                         std::string tag,
                                                         int row) { onRowRemoved(item, tag, row); },
                                                  this);

        m_rootItem = model->rootItem();
    }

    init_view_model();
}

//! Returns root item of the model. Can be different from model's root item when the intention is
//! to show only part of the model.

SessionItem* ViewModel::rootSessionItem() const
{
    return m_rootItem;
}

//! Returns QStandardItem associated with top level item (rootSessionItem).

QStandardItem* ViewModel::rootStandardItem() const
{
    return invisibleRootItem();
}

//! Returns vector of standard views used to display given SessionItem.

std::vector<QStandardItem*> ViewModel::findStandardViews(const SessionItem* item) const
{
    if (item == rootSessionItem())
        return {rootStandardItem()};

    std::vector<QStandardItem*> result;
    for (auto view : findViews(item))
        result.push_back(view);

    return result;
}

std::vector<ViewItem*> ViewModel::findViews(const SessionItem* item) const
{
    return Utils::findViews(this, QModelIndex(), item);
}

SessionItem* ViewModel::sessionItemFromIndex(const QModelIndex& index) const
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

QModelIndexList ViewModel::indexOfSessionItem(const SessionItem* item) const
{
    QModelIndexList result;
    for (auto view : findStandardViews(item))
        result.push_back(indexFromItem(view));
    return result;
}

void ViewModel::setRootSessionItem(SessionItem* item)
{
    if (item->model() != m_sessionModel)
        throw std::runtime_error(
            "ViewModel::setRootSessionItem()->Error. Item doesn't belong to a model.");

    m_rootItem = item;
    init_view_model();
}

void ViewModel::onDataChange(SessionItem* item, int role)
{
    Q_UNUSED(item)
    Q_UNUSED(role)
}

void ViewModel::onRowInserted(SessionItem* parent, std::string tag, int row)
{
    Q_UNUSED(parent)
    Q_UNUSED(tag)
    Q_UNUSED(row)
}

void ViewModel::onRowRemoved(SessionItem* parent, std::string tag, int row)
{
    Q_UNUSED(parent)
    Q_UNUSED(tag)
    Q_UNUSED(row)
}
