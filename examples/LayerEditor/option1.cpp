#include "option1.h"
#include "customtableview.h"
#include "materialmodel.h"
#include "treemodel.h"
#include "tableviewdelegate.h"
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>

Option1Widget::Option1Widget(QWidget* parent)
    : QWidget(parent)
    , m_material_view(new QTableView)
    , m_sample_view(new CustomTableView)
    , m_sample_model_view(new QTreeView)
    , m_material_model(MaterialModel::create())
    , m_sample_model(new TreeModel)
{
    auto layout_h = new QHBoxLayout;

    layout_h->addLayout(createMaterialPanel(), 3);
    layout_h->addLayout(createMultilayerPanel(), 3);

    m_sample_model_view->setModel(m_sample_model);
    m_sample_model_view->expandAll();
    layout_h->addWidget(m_sample_model_view, 2);

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
    material_filter->setEnabled(false);
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

    m_material_view->setModel(m_material_model);
    m_material_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_material_view->verticalHeader()->setVisible(false);

    layout->addLayout(layout_ht);
    layout->addWidget(m_material_view);
    layout->addLayout(layout_hb);
    return layout;
}

QVBoxLayout* Option1Widget::createMultilayerPanel()
{
    auto layout = new QVBoxLayout;
    auto layout_h = new QHBoxLayout;

    layout_h->addStretch();

    auto add_layer = new QPushButton;
    connect(add_layer, &QPushButton::clicked,
            [&]() { m_sample_model->insertLayers(1, m_sample_view->currentIndex()); });
    add_layer->setText("Add layer");
    layout_h->addWidget(add_layer);

    auto add_assembly = new QPushButton;
    connect(add_assembly, &QPushButton::clicked,
            [&]() { m_sample_model->insertAssemblies(1, m_sample_view->currentIndex()); });
    add_assembly->setText("Add assembly");
    layout_h->addWidget(add_assembly);

    auto remove_layer = new QPushButton;
    connect(remove_layer, &QPushButton::clicked, [&]() {
        m_sample_model->removeRow(m_sample_view->currentIndex().row(),
                                  m_sample_view->currentIndex());
    });
    remove_layer->setText("Remove row");
    layout_h->addWidget(remove_layer);

    m_sample_view->setModel(m_sample_model);
    m_sample_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_sample_view->setItemDelegate(new TableViewDelegate(m_sample_view));

    layout->addWidget(m_sample_view);
    layout->addLayout(layout_h);
    return layout;
}
