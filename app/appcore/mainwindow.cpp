// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mainwindow.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QDebug>

namespace {
QList<QStandardItem*> get_items(int n_items, const QString& prefix) {
    QList<QStandardItem*> result;

    for (int col=0; col<n_items; ++col)
        result.append(new QStandardItem(QString("%0 %1").arg(prefix).arg(col)));

    return result;
}
}


MainWindow::MainWindow()
    : m_treeView(new QTreeView)
    , m_model(new QStandardItemModel(this))
{    
    m_model->setColumnCount(3);
    QStandardItem *parentItem = m_model->invisibleRootItem();

    auto item_row1 = get_items(3, "aaa");
    parentItem->appendRow(item_row1);
    item_row1.at(0)->appendRow(get_items(2, "bbb"));

    auto item_row2 = get_items(3, "aaa");
    parentItem->appendRow(item_row2);
    item_row2.at(0)->appendRow(get_items(2, "ccc"));

    m_treeView->setModel(m_model);
    setCentralWidget(m_treeView);
    resize(800, 600);
}
