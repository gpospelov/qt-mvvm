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
    selector_t open_dir;
    selector_t create_dir;

    ProjectManagerImpl(ApplicationModelsInterface* models, selector_t open_dir,
                       selector_t create_dir)
        : app_models(models), current_project(ProjectUtils::CreateUntitledProject(models)),
          open_dir(open_dir), create_dir(create_dir)
    {
    }

    //! Closes current project. Used in assumption that project was already saved.
    void closeCurrentProject()
    {
        if (!current_project)
            return;
        current_project.reset();
    }

    //! Returns true if the project has directory already defined.
    bool projectHasDir() const { return !current_project->projectDir().empty(); }

    //! Saves project in project directory. If directory is not defined
    bool saveCurrentProject()
    {
        if (!current_project)
            return succeeded;
        auto save_dir = projectHasDir() ? current_project->projectDir() : create_dir();
        return saveCurrentProjectAs(save_dir);
    }

    //! Saves the project into a given directory.

    bool saveCurrentProjectAs(const std::string& dirname)
    {
        // empty directory means 'cancel' during directory selection
        return dirname.empty() ? failed : current_project->save(dirname);
    }
};

//! Constructor for ProjectManager. Requires ApplicationModels and two callbacks to open projects,
//! and create new projects.

ProjectManager::ProjectManager(ApplicationModelsInterface* app_models, selector_t open_dir,
                               selector_t create_dir)
    : p_impl(std::make_unique<ProjectManagerImpl>(app_models, open_dir, create_dir))
{
}

ProjectManager::~ProjectManager() = default;

bool ProjectManager::createNewProject()
{
    if (!p_impl->saveCurrentProject())
        return failed;
    p_impl->closeCurrentProject();
    p_impl->current_project = ProjectUtils::CreateUntitledProject(p_impl->app_models);
    return succeeded;
}

bool ProjectManager::saveCurrentProject()
{
    return p_impl->saveCurrentProject();
}

//! Saves project under the name provided by create_dir callback.
//! Directory has to be created by the callback.

bool ProjectManager::saveProjectAs()
{
    auto dirname = p_impl->create_dir();
    return p_impl->saveCurrentProjectAs(dirname);
}

bool ProjectManager::openExistingProject()
{
    return succeeded;
    //    if (!p_impl->saveCurrentProject())
    //        return;
    //    p_impl->closeCurrentProject();
}

std::string ProjectManager::currentProjectDir() const
{
    return p_impl->current_project ? p_impl->current_project->projectDir() : std::string();
}
