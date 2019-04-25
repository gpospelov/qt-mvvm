#include "initiallayereditor.h"
#include "layereditorutils.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

InitialLayerEditor::InitialLayerEditor(QWidget *parent) : QWidget(parent)
{
    auto material_filter = new QComboBox;
    material_filter->addItem("Scattering length density  ");
    material_filter->addItem("Refractive index");

    auto layout_ht = new QHBoxLayout;
    layout_ht->addWidget(new QLabel("Material description"));
    layout_ht->addWidget(material_filter);
    layout_ht->addStretch();

    auto table = LayerEditorUtils::createLayerTable();

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
