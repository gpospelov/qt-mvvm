// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "defaultviewmodel.h"
#include "itemutils.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewitems.h"
#include "rowconstructor.h"
#include <QDebug>
#include <algorithm>

using namespace ModelView;

namespace
{

QVector<int> item_role_to_qt(int role) {
    QVector<int> result;
    if (role == ItemDataRole::DISPLAY || role == ItemDataRole::DATA)
        result = {Qt::DisplayRole, Qt::EditRole};

    return result;
}

}

DefaultViewModel::DefaultViewModel(QObject* parent) : QStandardItemModel(parent),
    m_sessionModel(nullptr),
    m_row_constructor(new DefaultRowConstructor)
{
    setItemPrototype(new ViewEmptyItem);
}

DefaultViewModel::~DefaultViewModel() = default;

void DefaultViewModel::setSessionModel(SessionModel* model)
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
            onRowRemoved(item, row, id); }, this);
    }

    clear();
    setColumnCount(2);

    update_model();
}

//! Returns list of ViewItems representing given item.

QList<QStandardItem*> DefaultViewModel::findViews(SessionItem* item)
{
    QList<QStandardItem*> result;

    return result;
}

void DefaultViewModel::onDataChange(SessionItem* item, int role)
{
    Q_UNUSED(item);
    Q_UNUSED(role);
    qDebug() << "DefaultViewModel::onDataChange";
}

void DefaultViewModel::onRowInserted(SessionItem* parent, int row)
{
    Q_UNUSED(parent);
    Q_UNUSED(row);
    qDebug() << "DefaultViewModel::onRowInserted";

}

void DefaultViewModel::onRowRemoved(SessionItem* parent, int row, std::string id)
{
    Q_UNUSED(parent);
    Q_UNUSED(row);
    Q_UNUSED(id);
    qDebug() << "DefaultViewModel::onRowRemoved";
}

void DefaultViewModel::update_model()
{
    if (!m_sessionModel)
        return;

    qDebug() << "DefaultViewModel::update_model";
    iterate(m_sessionModel->rootItem(), invisibleRootItem());
}

void DefaultViewModel::iterate(SessionItem* item, QStandardItem* parent)
{
    qDebug() << "DefaultViewModel::iterate";

    QStandardItem* origParent(parent);
    for (auto child : item->children()) {

        auto row = m_row_constructor->constructRow(child);
        qDebug() << "aaa" << row.size();
        parent->appendRow(row);

        if (row.size())
            parent = row.at(0); // labelItem

        iterate(child, parent);
        parent = origParent;
    }

}
