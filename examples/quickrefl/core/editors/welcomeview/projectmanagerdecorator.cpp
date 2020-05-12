// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectmanagerdecorator.h"
#include "applicationmodelsinterface.h"
#include "projectinterface.h"
#include "projectmanager.h"

namespace
{
const bool succeeded = true;
const bool failed = false;
} // namespace

struct ProjectManagerDecorator::ProjectManagerImpl {
    ApplicationModelsInterface* app_models{nullptr};
    std::unique_ptr<ProjectManager> project_manager;
    selector_t open_dir;
    selector_t create_dir;
    answer_callback_t save_callback;

    ProjectManagerImpl(ApplicationModelsInterface* models, selector_t open_dir,
                       selector_t create_dir)
        : app_models(models), project_manager(std::make_unique<ProjectManager>(models)),
          open_dir(open_dir), create_dir(create_dir)
    {
    }

    //! Returns true if the project has directory already defined.
    bool projectHasDir() const { return !project_manager->currentProjectDir().empty(); }

    //    //! Saves project in project directory. If directory is not defined
    bool saveCurrentProject()
    {
        auto save_dir =
            projectHasDir() ? project_manager->currentProjectDir() : acquireNewProjectDir();
        return saveCurrentProjectAs(save_dir);
    }

    bool saveCurrentProjectAs(const std::string& dirname)
    {
        // empty directory means 'cancel' during directory selection
        return dirname.empty() ? failed : project_manager->saveProjectAs(dirname);
    }

    std::string currentProjectDir() const { return project_manager->currentProjectDir(); }

    bool isModified() const { return project_manager->isModified(); }

    bool saveBeforeClosing()
    {
        if (isModified()) {
            switch (acquireSaveChangesAnswer()) {
            case SAVE:
                return saveCurrentProject();
            case CANCEL:
                return failed; // saving was interrupted by cancel
            case DISCARD:
                project_manager->closeWithoutSaving();
                return succeeded;
            default:
                throw std::runtime_error("Error in ProjectManager: unexpected answer.");
            }
        }
        return succeeded;
    }

    SaveChangesAnswer acquireSaveChangesAnswer() const
    {
        if (!save_callback)
            throw std::runtime_error("Error in ProjectManager: absent save_callback");
        return save_callback();
    }

    std::string acquireNewProjectDir()
    {
        if (!create_dir)
            throw std::runtime_error("Error in ProjectManager: absent creat_dir callback.");
        return create_dir();
    }

    std::string acquireExistingProjectDir()
    {
        if (!open_dir)
            throw std::runtime_error("Error in ProjectManager: absent open_dir callback.");
        return open_dir();
    }
};

//! Constructor for ProjectManager. Requires ApplicationModels and two callbacks to open projects,
//! and create new projects.

ProjectManagerDecorator::ProjectManagerDecorator(ApplicationModelsInterface* app_models,
                                                 selector_t open_dir, selector_t create_dir)
    : p_impl(std::make_unique<ProjectManagerImpl>(app_models, open_dir, create_dir))
{
}

void ProjectManagerDecorator::setSaveChangesAnswerCallback(answer_callback_t save_callback)
{
    p_impl->save_callback = save_callback;
}

ProjectManagerDecorator::~ProjectManagerDecorator() = default;

bool ProjectManagerDecorator::createNewProject(const std::string&)
{
    if (!p_impl->saveBeforeClosing())
        return failed;

    auto project_dir = p_impl->acquireNewProjectDir();
    // empty dir denotes 'cancel' during directory creaion dialog
    return project_dir.empty() ? failed : p_impl->project_manager->createNewProject(project_dir);
}

bool ProjectManagerDecorator::saveCurrentProject()
{
    return p_impl->saveCurrentProject();
}

//! Saves project under the name provided by create_dir callback.
//! Directory has to be created by the callback.

bool ProjectManagerDecorator::saveProjectAs(const std::string&)
{
    auto project_dir = p_impl->acquireNewProjectDir();
    // empty dir denotes 'cancel' during directory creaion dialog
    return project_dir.empty() ? failed : p_impl->saveCurrentProjectAs(project_dir);
}

bool ProjectManagerDecorator::openExistingProject(const std::string&)
{
    if (!p_impl->saveBeforeClosing())
        return failed;
    auto project_dir = p_impl->acquireExistingProjectDir();
    // empty dir denotes 'cancel' during directory creaion dialog
    return project_dir.empty() ? failed : p_impl->project_manager->openExistingProject(project_dir);
}

std::string ProjectManagerDecorator::currentProjectDir() const
{
    return p_impl->currentProjectDir();
}

bool ProjectManagerDecorator::isModified() const
{
    return p_impl->isModified();
}
