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
#include "samplemodel.h"
#include "userinteractor.h"
#include <mvvm/project/projectmanagerdecorator.h>

using namespace ModelView;

ProjectHandler::ProjectHandler(SampleModel* sample_model, QObject* parent)
    : QObject(parent), m_recentProjectSettings(std::make_unique<RecentProjectSettings>()),
      m_userInteractor(std::unique_ptr<UserInteractor>()), m_model(sample_model)
{
    init_project_manager();
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

void ProjectHandler::update_current_project_name() {}

void ProjectHandler::update_recent_project_names() {}
