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
#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QScreen>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <mvvm/project/projectutils.h>
#include <mvvm/widgets/widgetutils.h>

namespace
{
int max_recent_project_count = 7;
}

RecentProjectWidget::RecentProjectWidget(QWidget* parent)
    : QWidget(parent), m_current_project_pane(new ProjectPaneWidget)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 0, 10, 0);
    layout->addSpacing(ModelView::Utils::HeightOfLetterM());
    layout->addLayout(createCurrentProjectLayout());
    layout->addSpacing(ModelView::Utils::HeightOfLetterM());
    layout->addLayout(createRecentProjectLayout());
    layout->addStretch(1);
}

//! Set current project title and label on appropriate widget.
void RecentProjectWidget::setCurrentProject(const QString& project_dir, bool is_modified)
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

QSize RecentProjectWidget::sizeHint() const
{
    const auto panel_width = ModelView::Utils::WidthOfLetterM() * 32;
    return QSize(panel_width, panel_width * 2);
}

QSize RecentProjectWidget::minimumSizeHint() const
{
    const auto minimum_panel_width = ModelView::Utils::WidthOfLetterM() * 16;
    return QSize(minimum_panel_width, minimum_panel_width * 2);
}

QBoxLayout* RecentProjectWidget::createCurrentProjectLayout() const
{
    auto result = new QVBoxLayout;
    auto label = new QLabel("Current Project");
    //    label->setFont(StyleUtils::sectionFont());
    result->addWidget(label);
    result->addWidget(m_current_project_pane);
    return result;
}

QBoxLayout* RecentProjectWidget::createRecentProjectLayout()
{
    auto result = new QVBoxLayout;
    auto label = new QLabel("Recent Projects");
    //    label->setFont(StyleUtils::sectionFont());
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
