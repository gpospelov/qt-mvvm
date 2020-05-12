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
#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>

RecentProjectWidget::RecentProjectWidget(QWidget* parent)
    : QWidget(parent), m_current_project_label(new QLabel("Untitled")),
      m_current_project_path(new QLabel("~/development/projects/Untitled"))
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

QBoxLayout* RecentProjectWidget::createCurrentProjectLayout() const
{
    auto result = new QVBoxLayout;
    result->setContentsMargins(30, 0, 0, 0);

    auto label = new QLabel("Current Project:");
    label->setFont(StyleUtils::sectionFont());
    result->addWidget(label);
    result->addWidget(m_current_project_label);
    result->addWidget(m_current_project_path);

    return result;
}
