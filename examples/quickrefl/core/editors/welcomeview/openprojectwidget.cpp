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
    layout->addLayout(createTempButtonLayout());
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
    connect(new_project_button, &QPushButton::pressed, this,
            &OpenProjectWidget::createNewProjectRequest);

    open_project_button = new QPushButton("Open");
    open_project_button->setMinimumHeight(StyleUtils::LargeButtonHeight());
    open_project_button->setMinimumWidth(200);
    open_project_button->setFont(StyleUtils::sectionFont());
    connect(open_project_button, &QPushButton::pressed, this,
            &OpenProjectWidget::openExistingProjectRequest);

    result->addStretch(1);
    result->addWidget(new_project_button);
    result->addWidget(open_project_button);
    result->addStretch(1);

    return result;
}

//! Temporary layou for save and save-as buttons.
QBoxLayout *OpenProjectWidget::createTempButtonLayout()
{
    auto result = new QHBoxLayout;

    save_project_button = new QPushButton("Save");
    save_project_button->setMinimumHeight(StyleUtils::LargeButtonHeight());
    save_project_button->setMinimumWidth(200);
    save_project_button->setFont(StyleUtils::sectionFont());
    connect(save_project_button, &QPushButton::pressed, this,
            &OpenProjectWidget::saveProjectRequest);

    saveas_project_button = new QPushButton("Open");
    saveas_project_button->setMinimumHeight(StyleUtils::LargeButtonHeight());
    saveas_project_button->setMinimumWidth(200);
    saveas_project_button->setFont(StyleUtils::sectionFont());
    connect(saveas_project_button, &QPushButton::pressed, this,
            &OpenProjectWidget::saveAsProjectRequest);

    result->addStretch(1);
    result->addWidget(save_project_button);
    result->addWidget(saveas_project_button);
    result->addStretch(1);

    return result;

}
