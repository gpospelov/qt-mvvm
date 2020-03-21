// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "centralwidget.h"
#include "colorlisteditor.h"
#include <QGridLayout>
#include <QItemEditorFactory>
#include <QStandardItemModel>
#include <QTableView>
#include <QTreeView>

namespace
{

QList<QStandardItem*> createRow(QVector<QVariant> data)
{
    QList<QStandardItem*> result;
    for (auto value : data) {
        auto item = new QStandardItem;
        item->setData(value, Qt::EditRole);
        result.append(item);
    }
    return result;
}
} // namespace

CentralWidget::CentralWidget(QWidget* parent) : QWidget(parent), model(new QStandardItemModel)
{
    init_model();
//    init_factory();

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
    QVector<QVariant> data = {QVariant::fromValue(42), QVariant::fromValue(42.1), QVariant::fromValue(QColor(Qt::red))};
    QStandardItem* parentItem = model->invisibleRootItem();
    parentItem->appendRow(createRow(data));
    parentItem->appendRow(createRow(data));
}

void CentralWidget::init_factory()
{
    QItemEditorFactory* factory = new QItemEditorFactory;

    QItemEditorCreatorBase* colorListCreator = new QStandardItemEditorCreator<ColorListEditor>();

    factory->registerEditor(QVariant::Color, colorListCreator);

    QItemEditorFactory::setDefaultFactory(factory);
}
