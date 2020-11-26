// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphwidgettoolbar.h"
#include <QDebug>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>

namespace
{
const int initial_value = 50;
const int min_value = 0;
const int max_value = 100;
} // namespace

GraphWidgetToolBar::GraphWidgetToolBar(QWidget* parent)
    : QToolBar(parent)
    , value_box(new QSpinBox)
    , value_slider(new QSlider)
    , delay_spinbox(new QSpinBox)
    , progressbar(new QProgressBar)
    , cancel_button(new QPushButton)
{
    const int toolbar_icon_size = 24;
    setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    init_value_elements();
    add_wide_separator();

    init_delay_elements();
    add_wide_separator();

    init_flow_elements();
}

//! Set progress bar to given value.

void GraphWidgetToolBar::onProgressChanged(int value)
{
    progressbar->setValue(value);
}

void GraphWidgetToolBar::add_wide_separator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

//! Inits elements to edit initial simulation parameter.

void GraphWidgetToolBar::init_value_elements()
{
    const QString tooltip = "Input parameter of background simulation.\n"
                            "Any change triggers new simulation and subsequent replot.";

    auto label = new QLabel("Amplitude");
    label->setToolTip(tooltip);
    addWidget(label);

    // Value box setup.
    value_box->setValue(initial_value);
    value_box->setRange(min_value, max_value);
    value_box->setMinimumWidth(100);
    value_box->setToolTip(tooltip);
    value_box->setKeyboardTracking(false);
    addWidget(value_box);

    auto on_value_changed = [this](int value) {
        value_slider->setValue(value);
        this->valueChanged(value);
    };
    connect(value_box, QOverload<int>::of(&QSpinBox::valueChanged), on_value_changed);

    // Slider setup.
    value_slider->setOrientation(Qt::Horizontal);
    value_slider->setRange(min_value, max_value);
    value_slider->setValue(initial_value);
    value_slider->setMaximumWidth(400);
    value_slider->setToolTip(tooltip);
    addWidget(value_slider);

    auto on_slider_changed = [this](int value) { value_box->setValue(value); };
    connect(value_slider, &QSlider::valueChanged, on_slider_changed);
}

//! Inits label and sping box to edit simulation slowdown factor.

void GraphWidgetToolBar::init_delay_elements()
{
    const QString tooltip = "Delay affects the duration of background simulation.\n"
                            "Given in microseconds per one point of the graph.";
    auto label = new QLabel("Delay");
    label->setToolTip(tooltip);
    addWidget(label);

    delay_spinbox->setRange(0, 50000);
    delay_spinbox->setMinimumWidth(100);
    addWidget(delay_spinbox);

    connect(delay_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), this,
            &GraphWidgetToolBar::delayChanged);
    delay_spinbox->setValue(1000);
}

//! Inits progress bar and button to cancel running simulation.

void GraphWidgetToolBar::init_flow_elements()
{
    progressbar->setMaximumWidth(300);
    addWidget(progressbar);

    auto placeholder = new QWidget;
    placeholder->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    addWidget(placeholder);

    cancel_button->setText("Cancel Simulation");
    addWidget(cancel_button);
    connect(cancel_button, &QPushButton::pressed, this, &GraphWidgetToolBar::cancelPressed);
}
