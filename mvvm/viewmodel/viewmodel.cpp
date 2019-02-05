// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodel.h"
#include "itemutils.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewitems.h"
#include <QDebug>
#include <algorithm>

using namespace ModelView;

namespace
{

//! Constructs row (display name and data) for given item.
std::vector<ViewItem*> constructRow(SessionItem* item)
{
    std::vector<ViewItem*> result;
    result.push_back(new ViewLabelItem(item));
    if (item->data(ItemDataRole::DATA).isValid())
        result.push_back(new ViewDataItem(item));
    return result;
}

QList<QStandardItem*> toStandardItemList(const std::vector<ViewItem*>& items)
{
    QList<QStandardItem*> result;
    std::transform(items.begin(), items.end(), std::back_inserter(result),
                   [](ViewItem* item) { return item; });
    return result;
}
}

ViewModel::ViewModel(QObject* parent) : QStandardItemModel(parent), m_sessionModel(nullptr)
{
    setItemPrototype(new ViewEmptyItem);
}

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

        m_sessionModel->mapper()->setOnRowRemoved(
            [this](ModelView::SessionItem* item, int row) { onRowRemoved(item, row); }, this);
    }

    m_item_to_view.clear();
    clear();
    setColumnCount(2);

    update_model();
}

void ViewModel::onDataChange(SessionItem* item, int role)
{
    qDebug() << "ViewModel::onDataChange" << item << role;
}

void ViewModel::onRowInserted(SessionItem* parent, int row)
{
    (void)row;
    auto it = m_item_to_view.find(parent);
    auto parentView = it != m_item_to_view.end() ? it->second.at(0) : invisibleRootItem();
    iterate(parent, parentView);
}

void ViewModel::onRowRemoved(SessionItem* parent, int row)
{
    qDebug() << "ViewModel::onRowRemoved" << parent << row;
}

void ViewModel::update_model()
{
    if (!m_sessionModel)
        return;

    iterate(m_sessionModel->rootItem(), invisibleRootItem());
}

void ViewModel::iterate(SessionItem* item, QStandardItem* parent)
{
    QStandardItem* origParent(parent);
    int insert_index(0);
    for (auto child : item->children()) {

        std::vector<ViewItem*> row;

        auto it = m_item_to_view.find(child);
        if (it == m_item_to_view.end()) {
            row = constructRow(child);
            m_item_to_view[child] = row;
            if (row.size())
                parent->insertRow(insert_index, toStandardItemList(row));
        } else {
            row = it->second;
        }

        ++insert_index;

        if (row.size())
            parent = row.at(0); // labelItem

        iterate(child, parent);
        parent = origParent;
    }
}
