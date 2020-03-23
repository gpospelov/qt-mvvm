// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainbarwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>

MainBarWidget::MainBarWidget(QWidget* parent)
    : QWidget(parent), stacked_widget(new QStackedWidget), button_layout(new QHBoxLayout)
{
    button_layout->setContentsMargins(0, 0, 0, 0);

    auto layout = new QVBoxLayout;
    layout->addLayout(button_layout);
    layout->addWidget(stacked_widget);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);
}

MainBarWidget::~MainBarWidget() = default;

void MainBarWidget::addWidget(QWidget* widget, const QString& title)
{
    auto button = new QPushButton(title);
    int index = stacked_widget->addWidget(widget);
    auto on_button_pressed = [this, index]() {
        stacked_widget->setCurrentIndex(index);
    };
    connect(button, &QPushButton::pressed, on_button_pressed);

    button_layout->addWidget(button);
}

void MainBarWidget::setCurrentIndex(int index)
{
    stacked_widget->setCurrentIndex(index);
}
