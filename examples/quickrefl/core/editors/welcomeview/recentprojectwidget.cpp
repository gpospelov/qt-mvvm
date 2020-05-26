// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "recentprojectwidget.h"
#include "projectpanewidget.h"
#include "projectutils.h"
#include "styleutils.h"
#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QScreen>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>

namespace
{
int max_recent_project_count = 7;
}

RecentProjectWidget::RecentProjectWidget(QWidget* parent)
    : QWidget(parent), m_current_project_pane(new ProjectPaneWidget)
{
    //    QPalette palette;
    //    palette.setColor(QPalette::Window, Qt::lightGray);
    //    setAutoFillBackground(true);
    //    setPalette(palette);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 0, 10, 0);
    layout->addLayout(createCurrentProjectLayout());
    layout->addSpacing(StyleUtils::SizeOfLetterM().height());
    layout->addLayout(createRecentProjectLayout());
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

//! Set current project title and label on appropriate widget.
void RecentProjectWidget::setCurrentProject(const QString &project_dir, bool is_modified)
{
    m_current_project_pane->setCurrentProject(project_dir, is_modified);
    m_current_project_pane->setActive(false);
}

//! Set name of all recent projects to appropriate widgets.
void RecentProjectWidget::setRecentProjectsList(const QStringList& projects)
{
    int widget_index{0};
    for (auto widget : m_recent_project_panes) {
        if (widget_index < projects.size())
            widget->setCurrentProject(projects.at(widget_index), false);
         else
            widget->clear();

        ++widget_index;
    }
}

QBoxLayout* RecentProjectWidget::createCurrentProjectLayout() const
{
    auto result = new QVBoxLayout;
    auto label = new QLabel("Current Project");
    label->setFont(StyleUtils::sectionFont());
    result->addWidget(label);
    result->addWidget(m_current_project_pane);
    return result;
}

QBoxLayout* RecentProjectWidget::createRecentProjectLayout()
{
    auto result = new QVBoxLayout;
    auto label = new QLabel("Recent Projects");
    label->setFont(StyleUtils::sectionFont());
    result->addWidget(label);

    for (int i = 0; i < max_recent_project_count; ++i) {
        auto widget = new ProjectPaneWidget;
        connect(widget, &ProjectPaneWidget::projectSelected, this,
                &RecentProjectWidget::projectSelected);
        m_recent_project_panes.push_back(widget);
        result->addWidget(widget);
    }
    return result;
}
