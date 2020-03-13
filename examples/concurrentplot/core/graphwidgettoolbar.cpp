// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphwidgettoolbar.h"
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QDebug>

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

    init_slowdown_elements();
    add_wide_separator();

    init_flow_elements();
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
    value_box->setValue(initial_value);
    value_box->setRange(min_value, max_value);
    value_box->setMinimumWidth(100);
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
    addWidget(value_slider);

    auto on_slider_changed = [this](int value) {
        qDebug() << "Slider box changed";
        value_box->setValue(value);
        this->valueChanged(value);
    };
    connect(value_slider, &QSlider::valueChanged, on_slider_changed);

}

//! Inits label and sping box to edit simulation slowdown factor.

void GraphWidgetToolBar::init_slowdown_elements()
{
    const QString slowdown_tooltip = "Slowdown factor affects the duration \n"
                                     "of background simulation on slider move.";
    auto label = new QLabel("Slowdown");
    label->setToolTip(slowdown_tooltip);
    addWidget(label);

    slowdown_spinbox->setValue(10);
    addWidget(slowdown_spinbox);
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
