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
#include <mvvm/interfaces/applicationmodelsinterface.h>

namespace ModelView
{
class ProjectManagerInterface;
}

class RecentProjectSettings;
class UserInteractor;
class SampleModel;
class RecentProjectWidget;

//! Main class to coordinate all activity on user's request to create new project,
//! open existing one, or choose one of recent projects on disk.

// FIXME remove multiple inheritance when callback in Document will be implemented

class ProjectHandler : public QObject, public ModelView::ApplicationModelsInterface
{
    Q_OBJECT
public:
    explicit ProjectHandler(SampleModel* sample_model, RecentProjectWidget* project_widget);
    ~ProjectHandler() override;

    std::vector<ModelView::SessionModel*> persistent_models() const override;

signals:
    void currentProjectModified(const QString& project_dir, bool is_modified);
    void recentProjectsListModified(const QStringList& projects);

public slots:
    bool canCloseProject() const;
    void onCreateNewProject();
    void onOpenExistingProject(const QString& dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();

private:
    void initProjectManager();
    void updateNames();
    void updateCurrentProjectName();
    void updateRecentProjectNames();

    std::unique_ptr<RecentProjectSettings> m_recentProjectSettings;
    std::unique_ptr<UserInteractor> m_userInteractor;
    std::unique_ptr<ModelView::ProjectManagerInterface> m_projectManager;
    RecentProjectWidget* m_recentProjectWidget;
    SampleModel* m_model{nullptr};
};

#endif // PROJECTHANDLER_H
