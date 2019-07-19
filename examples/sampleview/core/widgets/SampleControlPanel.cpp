#include "SampleControlPanel.h"
#include "SampleTreeController.h"
#include <QHBoxLayout>
#include <QPushButton>

using namespace ModelView;

SampleControlPanel::SampleControlPanel(SampleTreeController& sample_controller, QWidget* parent)
    : QWidget(parent)
    , m_new_multilayer_button(new QPushButton(this))
    , m_new_layer_button(new QPushButton(this))
    , m_clone_button(new QPushButton(this))
    , m_remove_button(new QPushButton(this))
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
