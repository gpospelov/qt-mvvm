// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/project/projectmanagerdecorator.h"
#include "mvvm/project/project_types.h"
#include "mvvm/project/projectmanager.h"
#include <stdexcept>

using namespace ModelView;

namespace {
const bool succeeded = true;
const bool failed = false;
} // namespace

struct ProjectManagerDecorator::ProjectManagerImpl {
    ProjectContext m_project_context;
    UserInteractionContext m_user_context;
    std::unique_ptr<ProjectManager> project_manager;

    ProjectManagerImpl(ProjectContext project_context, UserInteractionContext user_context)
        : m_project_context(std::move(project_context)), m_user_context(std::move(user_context))
    {
        project_manager = std::make_unique<ProjectManager>(m_project_context);
    }

    //! Returns true if the project has directory already defined.
    bool projectHasDir() const { return !project_manager->currentProjectDir().empty(); }

    //! Saves project in project directory. If directory is not defined, will acquire
    //! directory susing callback provided.
    bool saveCurrentProject()
    {
        // Feature FIXME?: already saved project (i.e. isModified=false) will be saved again.
        // Files will be same, but creation date will be changed.

        auto save_dir =
            projectHasDir() ? project_manager->currentProjectDir() : acquireNewProjectDir();
        return saveCurrentProjectAs(save_dir);
    }

    //! Saves current project under directory selected.
    bool saveCurrentProjectAs(const std::string& dirname)
    {
        // empty dirname varible means 'cancel' during directory selection
        return dirname.empty() ? failed : project_manager->saveProjectAs(dirname);
    }

    std::string currentProjectDir() const { return project_manager->currentProjectDir(); }

    bool isModified() const { return project_manager->isModified(); }

    //! Performs saving of previous project before creating a new one.
    bool saveBeforeClosing()
    {
        if (isModified()) {
            switch (acquireSaveChangesAnswer()) {
            case SaveChangesAnswer::SAVE:
                return saveCurrentProject();
            case SaveChangesAnswer::CANCEL:
                return failed; // saving was interrupted by the 'cancel' button
            case SaveChangesAnswer::DISCARD:
                project_manager->closeCurrentProject();
                return succeeded;
            default:
                throw std::runtime_error("Error in ProjectManager: unexpected answer.");
            }
        }
        return succeeded;
    }

    //! Asks the user whether to save/cancel/discard the project using callback provided.
    SaveChangesAnswer acquireSaveChangesAnswer() const
    {
        if (!m_user_context.m_answer_callback)
            throw std::runtime_error("Error in ProjectManager: absent save_callback");
        return m_user_context.m_answer_callback();
    }

    //! Acquire the name of the new project directory using callback provided.
    std::string acquireNewProjectDir()
    {
        if (!m_user_context.m_create_dir_callback)
            throw std::runtime_error("Error in ProjectManager: absent creat_dir callback.");
        return m_user_context.m_create_dir_callback();
    }

    //! Acquire the name of the existing project directory using callback provided.
    std::string acquireExistingProjectDir()
    {
        if (!m_user_context.m_select_dir_callback)
            throw std::runtime_error("Error in ProjectManager: absent open_dir callback.");
        return m_user_context.m_select_dir_callback();
    }
};

//! Constructor for ProjectManagerDecorator.

ProjectManagerDecorator::ProjectManagerDecorator(const ProjectContext& project_context,
                                                 const UserInteractionContext& user_context)
    : p_impl(std::make_unique<ProjectManagerImpl>(project_context, user_context))
{
}

ProjectManagerDecorator::~ProjectManagerDecorator() = default;

//! Creates a new project in the directory 'dirname', returns 'true' in the case of success.
//! The directory should exist.
//! If provided name is empty, will call directory selector dialog using callback provided.
//! If current project is in unsaved state, will perform 'save-before-closing' procedure before
//! proceeding further.

bool ProjectManagerDecorator::createNewProject(const std::string& dirname)
{
    if (!p_impl->saveBeforeClosing())
        return failed;

    auto project_dir = dirname.empty() ? p_impl->acquireNewProjectDir() : dirname;
    // empty project_dir string denotes 'cancel' during directory creation dialog
    return project_dir.empty() ? failed : p_impl->project_manager->createNewProject(project_dir);
}

//! Saves current project, returns 'true' in the case of success.
//! The project should have a project directory defined, if it is not the case, it will
//! launch the procedure of directory selection using callback provided.

bool ProjectManagerDecorator::saveCurrentProject()
{
    return p_impl->saveCurrentProject();
}

//! Saves the project under a given directory, returns true in the case of success.
//! The directory should exist already. If provided 'dirname' variable is empty,
//! it will acquire a new project directory using dialog provided.

bool ProjectManagerDecorator::saveProjectAs(const std::string& dirname)
{
    auto project_dir = dirname.empty() ? p_impl->acquireNewProjectDir() : dirname;
    // empty project_dir variable denotes 'cancel' during directory creation dialog
    return project_dir.empty() ? failed : p_impl->saveCurrentProjectAs(project_dir);
}

//! Opens existing project, returns 'true' in the case of success.
//! If provided name is empty, will call directory selector dialog using callback provided.
//! If current project is in unsaved state, it will perform 'save-before-closing' procedure before
//! proceeding further.

bool ProjectManagerDecorator::openExistingProject(const std::string& dirname)
{
    if (!p_impl->saveBeforeClosing())
        return failed;
    auto project_dir = dirname.empty() ? p_impl->acquireExistingProjectDir() : dirname;
    // empty project_dir variable denotes 'cancel' during directory selection dialog
    return project_dir.empty() ? failed : p_impl->project_manager->openExistingProject(project_dir);
}

//! Returns current project directory.

std::string ProjectManagerDecorator::currentProjectDir() const
{
    return p_impl->currentProjectDir();
}

//! Returns true if project was modified since last save.

bool ProjectManagerDecorator::isModified() const
{
    return p_impl->isModified();
}

//! Closes current project, returns 'true' if succeeded.
//! Will show the dialog, via callback provided, asking the user whether to save/discard/cancel.
//! Returns 'false' only if user has selected 'cancel' button.

bool ProjectManagerDecorator::closeCurrentProject() const
{
    if (!p_impl->saveBeforeClosing())
        return failed;
    return succeeded;
}
