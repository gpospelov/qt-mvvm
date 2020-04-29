// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectmanager.h"
#include "applicationmodelsinterface.h"
#include "projectinterface.h"
#include "projectutils.h"

namespace
{
const bool succeeded = true;
const bool failed = false;
} // namespace

struct ProjectManager::ProjectManagerImpl {
    ApplicationModelsInterface* app_models{nullptr};
    std::unique_ptr<ProjectInterface> current_project;

    ProjectManagerImpl(ApplicationModelsInterface* models) : app_models(models) {}

    //! Closes current project. Used in assumption that project was already saved.
    void closeCurrentProject()
    {
        if (!current_project)
            return;
        current_project.reset();
    }

    //! Defines
    std::string acquireProjectDir() { return {}; }

    //! Returns true if the project has directory already defined.
    bool projectHasDir() const { return !current_project->projectDir().empty(); }

    //! Saves project in project directory. If directory is not defined
    bool saveCurrentProject()
    {
        if (!current_project)
            return succeeded;
        auto save_dir = projectHasDir() ? current_project->projectDir() : acquireProjectDir();
        // empty directory means 'cancel' during directory selection
        return save_dir.empty() ? failed : current_project->save(save_dir);
    }

    bool saveCurrentProjectAs()
    {
        if (!current_project)
            return succeeded;
        auto save_dir = projectHasDir() ? current_project->projectDir() : acquireProjectDir();
        // empty directory mean 'cancel'
        return save_dir.empty() ? failed : current_project->save(save_dir);
    }
};

ProjectManager::ProjectManager(ApplicationModelsInterface* app_models)
    : p_impl(std::make_unique<ProjectManagerImpl>(app_models))
{
    createNewProject();
}

ProjectManager::~ProjectManager() = default;

void ProjectManager::createNewProject()
{
    if (!p_impl->saveCurrentProject())
        return;
    p_impl->closeCurrentProject();
    p_impl->current_project = ProjectUtils::CreateUtitledProject(p_impl->app_models);
}

void ProjectManager::saveCurrentProject()
{
    p_impl->saveCurrentProject();
}

void ProjectManager::saveProjectAs() {}

void ProjectManager::openExistingProject()
{
    if (!p_impl->saveCurrentProject())
        return;
    p_impl->closeCurrentProject();
}

std::string ProjectManager::currentProjectDir() const
{
    return p_impl->current_project ? p_impl->current_project->projectDir() : std::string();
}
