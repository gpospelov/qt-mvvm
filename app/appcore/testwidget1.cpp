// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget1.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QDebug>

namespace
{
QList<QStandardItem*> get_items(int n_items, const QString& prefix)
{
    QList<QStandardItem*> result;

    for (int col = 0; col < n_items; ++col)
        result.append(new QStandardItem(QString("%0 %1").arg(prefix).arg(col)));

    return result;
}
}

TestWidget1::TestWidget1(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_model(new QStandardItemModel(this))
{
    auto layout = new QVBoxLayout;

//    m_model->setColumnCount(3);
    QStandardItem* parentItem = m_model->invisibleRootItem();

    auto item_row1 = get_items(1, "aaa");
    parentItem->appendRow(item_row1);
    item_row1.at(0)->appendRow(get_items(2, "bbb"));

    auto item_row2 = get_items(3, "aaa");
    parentItem->appendRow(item_row2);
    item_row2.at(0)->appendRow(get_items(2, "ccc"));

    m_treeView->setModel(m_model);

    layout->addWidget(m_treeView);

    setLayout(layout);

    connect(m_model, &QStandardItemModel::dataChanged, this, &TestWidget1::onDataChanged);
}

void TestWidget1::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles)
{
    qDebug() << topLeft << bottomRight << roles;
}
