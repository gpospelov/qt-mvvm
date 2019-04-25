#include "layereditorutils.h"
#include "treemodel.h"
#include <QHeaderView>
#include <QPixmap>
#include <QStandardItemModel>
#include <QTableWidget>

namespace
{
QStandardItem* createColorMapItem(Qt::GlobalColor color)
{
    QPixmap color_pixmap(20, 20);
    color_pixmap.fill(QColor(color));
    QStandardItem* item = new QStandardItem();
    item->setData(QVariant(color_pixmap), Qt::DecorationRole);
    return item;
}

QStandardItem* createLayer(const QString& name, const QString& thick, const QString& rough,
                                  const QString& material)
{
    auto layer = new QStandardItem(name);

    layer->setChild(0, 0, new QStandardItem("thickness"));
    layer->setChild(0, 1, new QStandardItem(thick));

    layer->setChild(1, 0, new QStandardItem("roughness"));
    layer->setChild(1, 1, new QStandardItem(rough));

    layer->setChild(2, 0, new QStandardItem("material"));
    layer->setChild(2, 1, new QStandardItem(material));
    return layer;
}
} // namespace

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

QTableWidget *LayerEditorUtils::createRepetitiveLayerTable()
{
    auto table = new QTableWidget();
    table->setRowCount(4);
    table->setColumnCount(5);

    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Repetitions"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem("Material"));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem("Thickness"));
    table->setHorizontalHeaderItem(4, new QTableWidgetItem("Roughness"));

    // top
    auto default_repertions = new QTableWidgetItem("1");
    default_repertions->setFlags(Qt::ItemIsSelectable);
    table->setItem(0, 0, default_repertions);

    table->setItem(0, 1, new QTableWidgetItem("top"));
    table->setItem(0, 2, new QTableWidgetItem("air"));

    auto default_val = new QTableWidgetItem("0.0");
    default_val->setFlags(Qt::ItemIsSelectable);
    table->setItem(0, 3, default_val);
    table->setItem(0, 4, default_val->clone());

    // assembly
    // assembly - layer 1

    table->setItem(1, 0, new QTableWidgetItem("10"));
    table->setItem(1, 1, new QTableWidgetItem("layer1"));
    table->setItem(1, 2, new QTableWidgetItem("mat1"));
    table->setItem(1, 3, new QTableWidgetItem("1.0"));
    table->setItem(1, 4, new QTableWidgetItem("0.1"));

    // assembly - layer 2

    table->setItem(2, 0, new QTableWidgetItem("10"));
    table->setItem(2, 1, new QTableWidgetItem("layer2"));
    table->setItem(2, 2, new QTableWidgetItem("sub"));
    table->setItem(2, 3, new QTableWidgetItem("2.0"));
    table->setItem(2, 4, new QTableWidgetItem("0.2"));

    // bottom

    table->setItem(3, 0, default_repertions->clone());
    table->setItem(3, 1, new QTableWidgetItem("bottom"));
    table->setItem(3, 2, new QTableWidgetItem("sub"));
    table->setItem(3, 3, default_val->clone());
    table->setItem(3, 4, new QTableWidgetItem("0.1"));

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setSpan(1, 0, 2, 1);
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

QStandardItemModel *LayerEditorUtils::createTreeLayerModel()
{
    auto model = new QStandardItemModel(3, 2);

    // header
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Value");

    QStandardItem* root_item = model->invisibleRootItem();

    // top layer
    auto top = createLayer("top", "0.0", "0.0", "air");

    auto thick_val = top->child(0, 1);
    thick_val->setFlags(Qt::ItemIsSelectable);

    auto rough_val = top->child(1, 1);
    rough_val->setFlags(Qt::ItemIsSelectable);

    root_item->setChild(0, 0, top);

    // assembly
    auto assembly = new QStandardItem("assembly");
    assembly->setChild(0, 0, new QStandardItem("Number of repetitions"));
    assembly->setChild(0, 1, new QStandardItem("10"));
    assembly->setChild(1, 0, createLayer("layer1", "1.0", "0.1", "mat1"));
    assembly->setChild(2, 0, createLayer("layer2", "2.0", "0.2", "sub"));

    root_item->setChild(1, 0, assembly);

    // bottom layer
    auto bottom = createLayer("bottom", "0.0", "0.1", "sub");
    thick_val = bottom->child(0, 1);
    thick_val->setFlags(Qt::ItemIsSelectable);

    root_item->setChild(2, 0, bottom);

    return model;
}

TreeModel *LayerEditorUtils::createCascadeLayerModel()
{
    // creating root item
    auto root_item = new AssemblyItem();
    root_item->setData(0, "root");
    root_item->setData(1, 1);

    // top layer
    auto top = new LayerItem();
    top->setData(0, "top");
    top->setData(1, "air");
    top->setData(2, "0.0");
    top->setData(3, "0.0");

    root_item->insertChild(0, top);

    // assembly
    auto assembly = new AssemblyItem();
    assembly->setData(0, "assembly");
    assembly->setData(1, 10);

    // assembly - layer 1
    auto layer1 = new LayerItem();
    layer1->setData(0, "layer1");
    layer1->setData(1, "mat1");
    layer1->setData(2, 1.0);
    layer1->setData(3, 0.1);

    assembly->insertChild(0, layer1);

    // assembly - layer 2
    auto layer2 = new LayerItem();
    layer2->setData(0, "layer2");
    layer2->setData(1, "sub");
    layer2->setData(2, 2.0);
    layer2->setData(3, 0.2);

    assembly->insertChild(1, layer2);

    root_item->insertChild(1, assembly);

    // bottom
    auto bottom = new LayerItem();
    bottom->setData(0, "bottom");
    bottom->setData(1, "sub");
    bottom->setData(2, 0.0);
    bottom->setData(3, 0.1);

    root_item->insertChild(2, bottom);

    // creating a model
    auto model = new TreeModel(root_item);
    return model;
}
