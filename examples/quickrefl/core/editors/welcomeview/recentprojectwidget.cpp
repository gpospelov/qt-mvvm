// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "recentprojectwidget.h"
#include "styleutils.h"
#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QScreen>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>

RecentProjectWidget::RecentProjectWidget(QWidget* parent)
    : QWidget(parent), m_current_project_title(new QLabel("Untitled")),
      m_current_project_dir(new QLabel("~/development/projects/Untitled"))
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::darkGray);
    setAutoFillBackground(true);
    setPalette(palette);

    auto layout = new QVBoxLayout(this);
    layout->addLayout(createCurrentProjectLayout());
    layout->addStretch(1);
}

QSize RecentProjectWidget::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize RecentProjectWidget::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

void RecentProjectWidget::setCurrentProject(const std::string& project_title,
                                            const std::string& project_dir)
{
    m_current_project_title->setText(QString::fromStdString(project_title));
    m_current_project_dir->setText(QString::fromStdString(project_dir));
    m_current_project_dir->setToolTip(QString::fromStdString(project_dir));
}

QBoxLayout* RecentProjectWidget::createCurrentProjectLayout() const
{
    auto result = new QVBoxLayout;
    result->setContentsMargins(30, 0, 0, 0);

    auto label = new QLabel("Current Project:");
    label->setFont(StyleUtils::sectionFont());
    result->addWidget(label);
    result->addWidget(m_current_project_title);
    result->addWidget(m_current_project_dir);

    return result;
}
