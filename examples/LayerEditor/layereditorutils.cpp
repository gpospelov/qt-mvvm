#include "layereditorutils.h"
#include <QHeaderView>
#include <QPixmap>
#include <QStandardItemModel>
#include <QTableWidget>

namespace {
    QStandardItem* createColorMapItem(Qt::GlobalColor color)
    {
        QPixmap color_pixmap(20,20);
        color_pixmap.fill(QColor(color));
        QStandardItem* item = new QStandardItem();
        item->setData(QVariant(color_pixmap), Qt::DecorationRole);
        return item;
    }
}

QTableWidget* LayerEditorUtils::createLayerTable()
{
    auto table = new QTableWidget();
    table->setRowCount(3);
    table->setColumnCount(6);

    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Material"));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem("Re(SLD)"));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem("Im(SLD)"));
    table->setHorizontalHeaderItem(4, new QTableWidgetItem("Thickness"));
    table->setHorizontalHeaderItem(5, new QTableWidgetItem("Roughness"));

    table->setItem(0, 0, new QTableWidgetItem("top"));
    table->setItem(0, 1, new QTableWidgetItem("air"));
    table->setItem(0, 2, new QTableWidgetItem("0.0"));
    table->setItem(0, 3, new QTableWidgetItem("0.0"));

    auto item1 = new QTableWidgetItem("0.0");
    item1->setFlags(Qt::ItemIsSelectable);
    table->setItem(0, 4, item1);

    auto item2 = new QTableWidgetItem("0.0");
    item2->setFlags(Qt::ItemIsSelectable);
    table->setItem(0, 5, item2);

    table->setItem(1, 0, new QTableWidgetItem("layer"));
    table->setItem(1, 1, new QTableWidgetItem("mat1"));
    table->setItem(1, 2, new QTableWidgetItem("1.0"));
    table->setItem(1, 3, new QTableWidgetItem("0.1"));
    table->setItem(1, 4, new QTableWidgetItem("100.0"));
    table->setItem(1, 5, new QTableWidgetItem("0.1"));

    table->setItem(2, 0, new QTableWidgetItem("bottom"));
    table->setItem(2, 1, new QTableWidgetItem("sub"));
    table->setItem(2, 2, new QTableWidgetItem("0.5"));
    table->setItem(2, 3, new QTableWidgetItem("0.01"));

    auto item3 = new QTableWidgetItem("0.0");
    item3->setFlags(Qt::ItemIsSelectable);
    table->setItem(2, 4, item3);

    table->setItem(2, 5, new QTableWidgetItem("0.1"));

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    return table;
}

QTableWidget* LayerEditorUtils::createShrinkedLayerTable()
{
    auto table = new QTableWidget();
    table->setRowCount(3);
    table->setColumnCount(4);

    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Material"));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem("Thickness"));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem("Roughness"));

    table->setItem(0, 0, new QTableWidgetItem("top"));
    table->setItem(0, 1, new QTableWidgetItem("air"));

    auto item1 = new QTableWidgetItem("0.0");
    item1->setFlags(Qt::ItemIsSelectable);
    table->setItem(0, 2, item1);

    auto item2 = new QTableWidgetItem("0.0");
    item2->setFlags(Qt::ItemIsSelectable);
    table->setItem(0, 3, item2);

    table->setItem(1, 0, new QTableWidgetItem("layer"));
    table->setItem(1, 1, new QTableWidgetItem("mat1"));
    table->setItem(1, 2, new QTableWidgetItem("100.0"));
    table->setItem(1, 3, new QTableWidgetItem("0.1"));

    table->setItem(2, 0, new QTableWidgetItem("bottom"));
    table->setItem(2, 1, new QTableWidgetItem("sub"));

    auto item3 = new QTableWidgetItem("0.0");
    item3->setFlags(Qt::ItemIsSelectable);
    table->setItem(2, 2, item3);

    table->setItem(2, 3, new QTableWidgetItem("0.1"));

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    return table;
}

QStandardItemModel* LayerEditorUtils::createMaterialModel()
{
    auto model = new QStandardItemModel(3, 4);

    // header
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Re(SLD)");
    model->setHeaderData(2, Qt::Horizontal, "Im(SLD)");
    model->setHeaderData(3, Qt::Horizontal, "Color");

    // row 0
    model->setItem(0, 0, new QStandardItem("air"));
    model->setItem(0, 1, new QStandardItem("0.0"));
    model->setItem(0, 2, new QStandardItem("0.0"));
    model->setItem(0, 3, createColorMapItem(Qt::yellow));

    // row 1
    model->setItem(1, 0, new QStandardItem("mat1"));
    model->setItem(1, 1, new QStandardItem("1.0"));
    model->setItem(1, 2, new QStandardItem("0.1"));
    model->setItem(1, 3, createColorMapItem(Qt::darkBlue));

    // row 2
    model->setItem(2, 0, new QStandardItem("sub"));
    model->setItem(2, 1, new QStandardItem("0.5"));
    model->setItem(2, 2, new QStandardItem("0.01"));
    model->setItem(2, 3, createColorMapItem(Qt::green));

    return model;
}
