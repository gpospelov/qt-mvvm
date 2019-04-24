#include "initiallayereditor.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

QTableWidget* InitialLayerEditor::createEditorTable()
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

QTableWidget* InitialLayerEditor::createShrinkedEditorTable()
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

InitialLayerEditor::InitialLayerEditor(QWidget *parent) : QWidget(parent)
{
    auto material_filter = new QComboBox;
    material_filter->addItem("Scattering length density  ");
    material_filter->addItem("Refractive index");

    auto layout_ht = new QHBoxLayout;
    layout_ht->addWidget(new QLabel("Material description"));
    layout_ht->addWidget(material_filter);
    layout_ht->addStretch();

    auto table = createEditorTable();

    auto layout_hb = new QHBoxLayout();

    auto add_layer = new QPushButton;
    add_layer->setText("Add layer");
    layout_hb->addWidget(add_layer);

    auto remove_layer = new QPushButton;
    remove_layer->setText("Remove layer");
    layout_hb->addWidget(remove_layer);
    layout_hb->addStretch();

    auto layout = new QVBoxLayout;
    layout->addLayout(layout_ht);
    layout->addWidget(table);
    layout->addLayout(layout_hb);
    setLayout(layout);
}
