// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTHANDLER_H
#define PROJECTHANDLER_H

#include <QObject>
#include <memory>
#include <vector>

namespace ModelView
{
class ProjectManagerInterface;
}

class RecentProjectSettings;
class UserInteractor;
class SampleModel;
class RecentProjectWidget;
class QMainWindow;

//! Main class to coordinate all activity on user's request to create new project,
//! open existing one, or choose one of recent projects on disk.

class ProjectHandler : public QObject
{
    Q_OBJECT

public:
    explicit ProjectHandler(SampleModel* sample_model, QMainWindow* main_window);
    ~ProjectHandler() override;

signals:
    void currentProjectModified(const QString& project_dir, bool is_modified);
    void recentProjectsListModified(const QStringList& projects);

public slots:
    void updateNames();
    bool canCloseProject() const;
    void onCreateNewProject();
    void onOpenExistingProject(const QString& dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();

private:
    void initProjectManager();
    void updateCurrentProjectName();
    void updateRecentProjectNames();

    std::unique_ptr<RecentProjectSettings> m_recentProjectSettings;
    std::unique_ptr<UserInteractor> m_userInteractor;
    std::unique_ptr<ModelView::ProjectManagerInterface> m_projectManager;
    SampleModel* m_model{nullptr};
};

#endif // PROJECTHANDLER_H
