// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projecthandler.h"
#include "recentprojectsettings.h"
#include "recentprojectwidget.h"
#include "samplemodel.h"
#include "userinteractor.h"
#include <QMainWindow>
#include <mvvm/project/projectmanagerdecorator.h>
#include <mvvm/widgets/widgetutils.h>

using namespace ModelView;

ProjectHandler::ProjectHandler(SampleModel* sample_model, QMainWindow* main_window)
    : QObject(main_window), m_recentProjectSettings(std::make_unique<RecentProjectSettings>()),
      m_userInteractor(
          std::make_unique<UserInteractor>(m_recentProjectSettings.get(), main_window)),
      m_model(sample_model)
{
    initProjectManager();
    updateRecentProjectNames();
}

ProjectHandler::~ProjectHandler() = default;

std::vector<SessionModel*> ProjectHandler::persistent_models() const
{
    return {m_model};
}

//! Update names (name of the current project, recent project name list, notifies the world).

void ProjectHandler::updateNames()
{
    updateCurrentProjectName();
    updateRecentProjectNames();
}

//! Returns 'true' if current project can be closed.
//! Internally will perform check for unsaved data, and proceed via save/discard/cancel dialog.

bool ProjectHandler::canCloseProject() const
{
    return m_projectManager->closeCurrentProject();
}

void ProjectHandler::onCreateNewProject()
{
    if (m_projectManager->createNewProject())
        updateNames();
}

void ProjectHandler::onOpenExistingProject(const QString& dirname)
{
    if (m_projectManager->openExistingProject(dirname.toStdString()))
        updateNames();
}

void ProjectHandler::onSaveCurrentProject()
{
    if (m_projectManager->saveCurrentProject())
        updateNames();
}

void ProjectHandler::onSaveProjectAs()
{
    if (m_projectManager->saveProjectAs())
        updateNames();
}

void ProjectHandler::initProjectManager()
{
    auto select_dir = [this]() { return m_userInteractor->onSelectDirRequest(); };
    auto create_dir = [this]() { return m_userInteractor->onCreateDirRequest(); };
    auto save_changes = [this]() { return m_userInteractor->onSaveChangesRequest(); };
    auto on_modified = [this]() { updateCurrentProjectName(); };

    auto manager =
        std::make_unique<ProjectManagerDecorator>(this, select_dir, create_dir, on_modified);
    manager->setSaveChangesAnswerCallback(save_changes);

    m_projectManager = std::move(manager);
}

//! Updates the name of the current project on main window, notifies the world.

void ProjectHandler::updateCurrentProjectName()
{
    const auto current_project_dir = QString::fromStdString(m_projectManager->currentProjectDir());
    const auto is_modified = m_projectManager->isModified();

    // set main window title
    auto title = ModelView::Utils::ProjectWindowTitle(current_project_dir, is_modified);
    if (auto main_window = ModelView::Utils::FindMainWindow(); main_window)
        main_window->setWindowTitle(title);

    currentProjectModified(current_project_dir, is_modified);
}

//! Update recent project list in settings, notifies the world.

void ProjectHandler::updateRecentProjectNames()
{
    m_recentProjectSettings->addToRecentProjects(
        QString::fromStdString(m_projectManager->currentProjectDir()));
    recentProjectsListModified(m_recentProjectSettings->recentProjects());
}
