// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef RECENTPROJECTWIDGET_H
#define RECENTPROJECTWIDGET_H

#include <QWidget>
#include <memory>
#include <vector>

class QBoxLayout;
class ProjectPaneWidget;

//! Widget with the name of current project and collection of recent projects.

class RecentProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecentProjectWidget(QWidget* parent = nullptr);

    void setCurrentProject(const QString& project_dir, bool is_modified);

    void setRecentProjectsList(const QStringList& projects);

    QSize sizeHint() const override;

    QSize minimumSizeHint() const override;

signals:
    void projectSelected(const QString& project_dir);

private:
    QBoxLayout* createCurrentProjectLayout() const;
    QBoxLayout* createRecentProjectLayout();
    QWidget* createRecentProjectScrollArea();
    ProjectPaneWidget* m_currentProjectPane{nullptr};
    std::vector<ProjectPaneWidget*> m_recentProjectPanes;
};

#endif // RECENTPROJECTWIDGET_H
