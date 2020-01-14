// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SampleControlPanel.h"
#include "QRCInitializer.h"
#include "SampleTreeController.h"
#include <QHBoxLayout>
#include <QPushButton>

const auto init = QRCInitializer::initSampleViewResources();

namespace
{
QPushButton* createButton(QWidget* parent, QIcon icon)
{
    QPushButton* result = new QPushButton(parent);
    result->setFlat(true);
    result->setIcon(icon);
    return result;
}
} // namespace

SampleControlPanel::SampleControlPanel(SampleTreeController& sample_controller, QWidget* parent)
    : QWidget(parent),
      m_new_multilayer_button(createButton(this, QIcon(":/icons/toolbar16dark_newitem.svg"))),
      m_new_layer_button(createButton(this, QIcon(":/icons/toolbar16dark_newitem.svg"))),
      m_clone_button(createButton(this, QIcon(":/icons/toolbar16dark_cloneitem.svg"))),
      m_remove_button(createButton(this, QIcon(":/icons/toolbar16dark_recycle.svg")))
{
    // setting connections
    connect(m_new_multilayer_button, &QPushButton::clicked, &sample_controller,
            &SampleTreeController::onCreateMultiLayer);
    connect(m_new_layer_button, &QPushButton::clicked, &sample_controller,
            &SampleTreeController::onCreateLayer);
    connect(m_clone_button, &QPushButton::clicked, &sample_controller,
            &SampleTreeController::onClone);
    connect(m_remove_button, &QPushButton::clicked, &sample_controller,
            &SampleTreeController::onRemove);

    // setting internal widgets to a layout
    auto layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_new_multilayer_button);
    layout->addWidget(m_new_layer_button);
    layout->addWidget(m_clone_button);
    layout->addWidget(m_remove_button);

    layout->addStretch(1);
}

SampleControlPanel::~SampleControlPanel() = default;
