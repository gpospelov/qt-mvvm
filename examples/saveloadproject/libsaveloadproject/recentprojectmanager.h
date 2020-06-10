// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef RECENTPROJECTMANAGER_H
#define RECENTPROJECTMANAGER_H

#include <QObject>
#include <memory>

namespace ModelView
{
class ProjectManagerInterface;
}

class RecentProjectSettings;
class UserInteractor;
class SampleModel;

//! Main class to coordinate all activity on user's request to create new project,
//! open existing one, or choose one of recent projects on disk.

class RecentProjectManager : public QObject
{
    Q_OBJECT
public:
    explicit RecentProjectManager(QObject* parent = nullptr);
    ~RecentProjectManager() override;

public slots:
    void onCreateNewProject();
    void onOpenExistingProject(const QString& dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();

private:
    void init_project_manager();
    void update_current_project_name();
    void update_recent_project_names();

    std::unique_ptr<RecentProjectSettings> m_recentProjectSettings;
    std::unique_ptr<UserInteractor> m_userInteractor;
    std::unique_ptr<ModelView::ProjectManagerInterface> m_projectManager;
    SampleModel* m_model{nullptr};
};

#endif // RECENTPROJECTMANAGER_H
