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
    : QToolBar(parent), value_box(new QSpinBox), value_slider(new QSlider),
      slowdown_spinbox(new QSpinBox), progressbar(new QProgressBar), cancel_button(new QPushButton)
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

//! Inits elements to edit initial simulation parameters.

void GraphWidgetToolBar::init_value_elements()
{
    const QString tooltip = "Input parameter of background simulation. \n"
                            "Any change triggers new simulation and subsequent replot.";

    auto label = new QLabel("Amplitude");
    label->setToolTip(tooltip);

    value_box->setValue(initial_value);
    value_box->setRange(min_value, max_value);
    value_box->setMinimumWidth(100);
    value_box->setToolTip(tooltip);

    //    auto on_value_changed = [this](int value) {
    //        qDebug() << "Spin box changed";
    //        value_slider->setValue(value);
    //        this->valueChanged(value);
    //    };
    //    connect(value_box, QOverload<int>::of(&QSpinBox::valueChanged), on_value_changed);

    auto on_editing_finished = [this]() {
        qDebug() << "Spin box editing finished";
        value_slider->setValue(value_box->value());
        this->valueChanged(value_box->value());
    };

    connect(value_box, &QSpinBox::editingFinished, on_editing_finished);
    addWidget(value_box);

    value_slider->setOrientation(Qt::Horizontal);
    value_slider->setRange(min_value, max_value);
    value_slider->setValue(initial_value);
    value_slider->setMaximumWidth(400);
    value_slider->setToolTip(tooltip);
    addWidget(value_slider);

    auto on_slider_changed = [this](int value) {
        qDebug() << "Slider box changed";
        value_box->setValue(value);
        this->valueChanged(value);
    };
    connect(value_slider, &QSlider::valueChanged, on_slider_changed);
}

//! Inits label and sping box to edit simulation slowdown factor.

void GraphWidgetToolBar::init_delay_elements()
{
    const QString tooltip = "Delay affects the duration of background simulation.";
    auto label = new QLabel("Delay");
    label->setToolTip(tooltip);
    addWidget(label);

    slowdown_spinbox->setValue(100);
    slowdown_spinbox->setMinimumWidth(100);
    addWidget(slowdown_spinbox);

    connect(value_box, QOverload<int>::of(&QSpinBox::valueChanged), this,
            &GraphWidgetToolBar::delayChanged);
}

void GraphWidgetToolBar::init_flow_elements()
{
    progressbar->setMaximumWidth(300);
    addWidget(progressbar);

    auto placeholder = new QWidget;
    placeholder->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    addWidget(placeholder);

    cancel_button->setText("Cancel Simulation");
    addWidget(cancel_button);
}
