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
}

void GraphWidgetToolBar::add_wide_separator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

void GraphWidgetToolBar::init_value_elements()
{
    value_box->setValue(initial_value);
    value_box->setRange(min_value, max_value);
    value_box->setMinimumWidth(100);
    addWidget(value_box);

    auto value_slider = new QSlider;
    value_slider->setOrientation(Qt::Horizontal);
    value_slider->setRange(min_value, max_value);
    value_slider->setValue(initial_value);
    value_slider->setMaximumWidth(500);
    addWidget(value_slider);
}

void GraphWidgetToolBar::init_slowdown_elements()
{
    auto label = new QLabel("Slowdown");
    label->setToolTip("Slowdown factor affects the duration of background simulation on slider move.");
    addWidget(label);
}
