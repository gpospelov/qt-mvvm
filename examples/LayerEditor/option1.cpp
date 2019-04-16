#include "option1.h"
#include "materialmodel.h"
#include "treemodel.h"
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QTreeView>
#include <QVBoxLayout>

Option1Widget::Option1Widget(QWidget* parent)
    : QWidget(parent)
    , m_tableView(new QTableView)
    , m_treeView(new QTreeView)
    , m_material_model(new MaterialModel)
    , m_sample_model(new TreeModel)
{
auto layout_h = new QHBoxLayout;

layout_h->addLayout(createMaterialPanel());
layout_h->addLayout(createMultilayerPanel());

setLayout(layout_h);
}

QVBoxLayout* Option1Widget::createMaterialPanel()
{
    auto layout = new QVBoxLayout;
    auto layout_ht = new QHBoxLayout;
    auto layout_hb = new QHBoxLayout;

    auto material_filter = new QComboBox;
    material_filter->addItem("Scattering length density  ");
    material_filter->addItem("Refractive index");
    layout_ht->addWidget(new QLabel("Material description"));
    layout_ht->addWidget(material_filter);
    layout_ht->addStretch();

    auto add_material = new QPushButton;
    add_material->setText("Add material");
    layout_hb->addWidget(add_material);

    auto remove_material = new QPushButton;
    remove_material->setText("Remove material");
    layout_hb->addWidget(remove_material);

    layout_hb->addStretch();

    m_tableView->setModel(m_material_model);
    m_tableView->setColumnHidden(m_material_model->columnCount()-1, true); // hiding material type
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addLayout(layout_ht);
    layout->addWidget(m_tableView);
    layout->addLayout(layout_hb);
    return layout;
}

QVBoxLayout* Option1Widget::createMultilayerPanel()
{
    auto layout = new QVBoxLayout;
    auto layout_h = new QHBoxLayout;

    layout_h->addStretch();

    auto add_layer  = new QPushButton;
    add_layer->setText("Add layer");
    layout_h->addWidget(add_layer);

    auto remove_layer = new QPushButton;
    remove_layer->setText("Remove layer");
    layout_h->addWidget(remove_layer);

    m_treeView->setModel(m_sample_model);
    m_treeView->expandAll();
    layout->addWidget(m_treeView);
    layout->addLayout(layout_h);
    return layout;
}
