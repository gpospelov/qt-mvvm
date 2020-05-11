// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "openprojectwidget.h"
#include "styleutils.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

OpenProjectWidget::OpenProjectWidget(QWidget* parent) : QWidget(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::darkBlue);
    setAutoFillBackground(true);
    setPalette(palette);

    auto layout = new QVBoxLayout(this);
    layout->addLayout(createButtonLayout());
}

QSize OpenProjectWidget::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize OpenProjectWidget::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

QBoxLayout* OpenProjectWidget::createButtonLayout()
{
    auto result = new QHBoxLayout;

    new_project_button = new QPushButton("New");
    new_project_button->setMinimumHeight(StyleUtils::LargeButtonHeight());
    new_project_button->setMinimumWidth(200);
    new_project_button->setFont(StyleUtils::sectionFont());

    open_project_button = new QPushButton("Open");
    open_project_button->setMinimumHeight(StyleUtils::LargeButtonHeight());
    open_project_button->setMinimumWidth(200);
    new_project_button->setFont(StyleUtils::sectionFont());

    result->addStretch(1);
    result->addWidget(new_project_button);
    result->addWidget(open_project_button);
    result->addStretch(1);

    return result;
}
