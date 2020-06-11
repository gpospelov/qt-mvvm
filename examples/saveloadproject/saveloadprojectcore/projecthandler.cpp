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

ProjectHandler::ProjectHandler(SampleModel* sample_model, RecentProjectWidget* project_widget)
    : QObject(project_widget), m_recentProjectSettings(std::make_unique<RecentProjectSettings>()),
      m_userInteractor(
          std::make_unique<UserInteractor>(project_widget, m_recentProjectSettings.get())),
      m_recentProjectWidget(project_widget), m_model(sample_model)
{
    init_project_manager();
    update_recent_project_names();
    connect(m_recentProjectWidget, &RecentProjectWidget::projectSelected, this,
            &ProjectHandler::onOpenExistingProject);
}

std::vector<SessionModel*> ProjectHandler::persistent_models() const
{
    return {m_model};
}

ProjectHandler::~ProjectHandler() = default;

void ProjectHandler::onCreateNewProject()
{
    if (m_projectManager->createNewProject()) {
        update_current_project_name();
        update_recent_project_names();
    }
}

void ProjectHandler::onOpenExistingProject(const QString& dirname)
{
    if (m_projectManager->openExistingProject(dirname.toStdString())) {
        update_current_project_name();
        update_recent_project_names();
    }
}

void ProjectHandler::onSaveCurrentProject()
{
    if (m_projectManager->saveCurrentProject()) {
        update_current_project_name();
        update_recent_project_names();
    }
}

void ProjectHandler::onSaveProjectAs()
{
    if (m_projectManager->saveProjectAs()) {
        update_current_project_name();
        update_recent_project_names();
    }
}

void ProjectHandler::init_project_manager()
{
    auto select_dir = [this]() { return m_userInteractor->onSelectDirRequest(); };
    auto create_dir = [this]() { return m_userInteractor->onCreateDirRequest(); };
    auto save_changes = [this]() { return m_userInteractor->onSaveChangesRequest(); };
    auto on_modified = [this]() { update_current_project_name(); };

    auto manager =
        std::make_unique<ProjectManagerDecorator>(this, select_dir, create_dir, on_modified);
    manager->setSaveChangesAnswerCallback(save_changes);

    m_projectManager = std::move(manager);
}

//! Updates the name of the current project on main window, notifies the world.

void ProjectHandler::update_current_project_name()
{
    const auto current_project_dir = QString::fromStdString(m_projectManager->currentProjectDir());
    const auto is_modified = m_projectManager->isModified();

    // set main window title
    auto title = ModelView::Utils::ProjectWindowTitle(current_project_dir, is_modified);
    if (auto main_window = ModelView::Utils::FindMainWindow(); main_window)
        main_window->setWindowTitle(title);

    // notifies the world
    m_recentProjectWidget->setCurrentProject(current_project_dir, is_modified);
}

//! Update recent project list in settings, notifies the world.

void ProjectHandler::update_recent_project_names()
{
    m_recentProjectSettings->addToRecentProjects(
        QString::fromStdString(m_projectManager->currentProjectDir()));
    m_recentProjectWidget->setRecentProjectsList(m_recentProjectSettings->recentProjects());
}
