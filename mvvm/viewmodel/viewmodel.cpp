// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodel.h"
#include "viewmodelutils.h"
#include "modelmapper.h"
#include "sessionmodel.h"

using namespace ModelView;

ViewModel::ViewModel(QObject* parent) : QStandardItemModel(parent), m_sessionModel(nullptr)
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
            [this](ModelView::SessionItem* item, int row) { onRowInserted(item, row); }, this);

        m_sessionModel->mapper()->setOnRowRemoved2(
            [this](ModelView::SessionItem* item, int row, std::string id) {
                onRowRemoved(item, row, id);
            },
            this);
    }

    init_view_model();
}

//! Returns root item of the model. Can be different from model's root item when the intention is
//! to show only part of the model.

SessionItem* ViewModel::rootSessionItem()
{
    return m_sessionModel->rootItem();
}

QStandardItem* ViewModel::rootStandardItem()
{
    return invisibleRootItem();
}

SessionModel* ViewModel::sessionModel()
{
    return m_sessionModel;
}

//! Returns vector of standard views used to display given SessionItem.

std::vector<QStandardItem*> ViewModel::findStandardViews(SessionItem* item)
{
    return Utils::findStandardViews(this, QModelIndex(), item);
}

// FIXME The only difference with the method above, is that we are not handling invisibleRootItem.
// Can both methods still be merged?

std::vector<ViewItem*> ViewModel::findViews(SessionItem* item)
{
    return Utils::findViews(this, QModelIndex(), item);
}

void ViewModel::onDataChange(SessionItem* item, int role)
{
    Q_UNUSED(item);
    Q_UNUSED(role);
}

void ViewModel::onRowInserted(SessionItem* parent, int row)
{
    Q_UNUSED(parent);
    Q_UNUSED(row);
}

void ViewModel::onRowRemoved(SessionItem* parent, int row, std::string id)
{
    Q_UNUSED(parent);
    Q_UNUSED(row);
    Q_UNUSED(id);
}
