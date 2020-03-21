// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "centralwidget.h"
#include <QGridLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QTreeView>

namespace
{
QList<QStandardItem*> createRow(QString text, int ncol)
{
    QList<QStandardItem*> result;
    for (int i = 0; i < ncol; ++i) {
        auto item = new QStandardItem(text);
        result.append(item);
    }
    return result;
}
} // namespace

CentralWidget::CentralWidget(QWidget* parent) : QWidget(parent), model(new QStandardItemModel)
{
    init_model();

    auto table0 = new QTableView;
    table0->setModel(model);

    auto table1 = new QTableView;
    table1->setModel(model);

    auto tree0 = new QTreeView;
    tree0->setModel(model);

    auto tree1 = new QTreeView;
    tree1->setModel(model);

    auto layout = new QGridLayout;
    layout->setSpacing(10);
    layout->addWidget(table0, 0, 0);
    layout->addWidget(table1, 0, 1);
    layout->addWidget(tree0, 1, 0);
    layout->addWidget(tree1, 1, 1);

    setLayout(layout);
}

void CentralWidget::init_model()
{
    QStandardItem* parentItem = model->invisibleRootItem();
    parentItem->appendRow(createRow("xxx", 4));
    parentItem->appendRow(createRow("xxx", 4));
}
