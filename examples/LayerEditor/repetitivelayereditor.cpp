#include "repetitivelayereditor.h"
#include "layereditorutils.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QTableWidget>
#include <QVBoxLayout>

RepetitiveLayerEditor::RepetitiveLayerEditor(QWidget* parent)
    : QWidget(parent)
    , m_material_view(new QTableView)
    , m_sample_table(LayerEditorUtils::createRepetitiveLayerTable())
    , m_material_model(LayerEditorUtils::createMaterialModel())
{
    auto layout_h = new QHBoxLayout;

    layout_h->addLayout(createMaterialPanel());
    layout_h->addLayout(createMultilayerPanel());

    setLayout(layout_h);
}

QVBoxLayout* RepetitiveLayerEditor::createMaterialPanel()
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

    m_material_view->setModel(m_material_model);
    m_material_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_material_view->verticalHeader()->setVisible(false);

    layout->addLayout(layout_ht);
    layout->addWidget(m_material_view);
    layout->addLayout(layout_hb);
    return layout;
}

QVBoxLayout* RepetitiveLayerEditor::createMultilayerPanel()
{
    auto layout = new QVBoxLayout;
    auto layout_h = new QHBoxLayout;

    layout_h->addStretch();

    auto add_layer = new QPushButton;
    add_layer->setText("Add layer");
    layout_h->addWidget(add_layer);

    auto remove_layer = new QPushButton;
    remove_layer->setText("Remove layer");
    layout_h->addWidget(remove_layer);

    layout->addWidget(m_sample_table);
    layout->addLayout(layout_h);
    return layout;
}
