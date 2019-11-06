// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MaterialControlPanel.h"
#include "MaterialViewController.h"
#include "QRCInitializer.h"
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>

const auto init = QRCInitializer::initSampleViewResources();

namespace {
QPushButton* createButton(QWidget* parent, QIcon icon)
{
    QPushButton* result = new QPushButton(parent);
    result->setFlat(true);
    result->setIcon(icon);
    return result;
}
}

using namespace ModelView;

MaterialControlPanel::MaterialControlPanel(MaterialViewController& view_control, QWidget* parent)
    : QWidget(parent)
    , m_new_button(createButton(this, QIcon(":/icons/toolbar16dark_newitem.svg")))
    , m_clone_button(createButton(this, QIcon(":/icons/toolbar16dark_cloneitem.svg")))
    , m_remove_button(createButton(this, QIcon(":/icons/toolbar16dark_recycle.svg")))
    , m_material_type_selector(new QComboBox(this))
{
    // setting connections
    m_material_type_selector->addItems(view_control.materialSets());
    connect(m_material_type_selector, qOverload<const QString&>(&QComboBox::currentTextChanged),
            &view_control, &MaterialViewController::onMaterialSelectionChange);

    connect(m_new_button, &QPushButton::clicked, &view_control,
            &MaterialViewController::onCreateMaterial);

    // clone operations
    m_clone_button->setEnabled(false);
    connect(m_clone_button, &QPushButton::clicked, &view_control,
            &MaterialViewController::onCloneMaterial);
    connect(&view_control, &MaterialViewController::rowCheckStateChanged, m_clone_button,
            [this](const QList<QModelIndex>& index_list) {
                m_clone_button->setEnabled(!index_list.empty());
            });

    // delete operations
    m_remove_button->setEnabled(false);
    connect(m_remove_button, &QPushButton::clicked, &view_control,
            &MaterialViewController::onRemoveMaterial);
    connect(&view_control, &MaterialViewController::rowCheckStateChanged, m_remove_button,
            [this](const QList<QModelIndex>& index_list) {
                m_remove_button->setEnabled(!index_list.empty());
            });

    // setting internal widgets to a layout
    auto layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_new_button);
    layout->addWidget(m_clone_button);
    layout->addWidget(m_remove_button);

    layout->addStretch(1);

    layout->addWidget(m_material_type_selector, 1);
}

MaterialControlPanel::~MaterialControlPanel() = default;
