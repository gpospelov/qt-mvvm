// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectmanager.h"
#include "project.h"
#include "applicationmodelsinterface.h"

struct ProjectManager::ProjectManagerImpl {
    ApplicationModelsInterface* app_models{nullptr};
    std::unique_ptr<Project> current_project;

    ProjectManagerImpl(ApplicationModelsInterface* models) : app_models(models) {}
};

ProjectManager::ProjectManager(ApplicationModelsInterface* app_models)
    : p_impl(std::make_unique<ProjectManagerImpl>(app_models))
{
}

ProjectManager::~ProjectManager() = default;

void ProjectManager::createNewProject()
{
}

void ProjectManager::saveCurrentProject()
{

}

void ProjectManager::saveProjectAs()
{

}

void ProjectManager::openExistingProject()
{

}
