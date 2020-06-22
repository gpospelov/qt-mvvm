// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECTMANAGER_H
#define MVVM_PROJECT_PROJECTMANAGER_H

#include <functional>
#include <memory>
#include <mvvm/interfaces/projectmanagerinterface.h>

namespace ModelView
{
class ApplicationModelsInterface;
}

//! Responsible for handling new/save/save-as/close Project logic, where the Project represents
//! a collection of serialized application models in the project directory.

//! This ProjectManager requires certain prerequisites to function properly: for example,
//! the creation of a new project will be possible only if the old project is in a saved state. See
//! description to the class methods.

class MVVM_MODEL_EXPORT ProjectManager : public ModelView::ProjectManagerInterface
{
public:
    using callback_t = std::function<void()>;
    ProjectManager(ModelView::ApplicationModelsInterface* app_models,
                   callback_t project_changed = {});
    ~ProjectManager() override;

    ProjectManager(const ProjectManager& other) = delete;
    ProjectManager& operator=(const ProjectManager& other) = delete;

    bool createNewProject(const std::string& dirname) override;

    bool saveCurrentProject() override;

    bool saveProjectAs(const std::string& dirname) override;

    bool openExistingProject(const std::string& dirname) override;

    std::string currentProjectDir() const override;

    bool isModified() const override;

    bool closeCurrentProject() const override;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

#endif // MVVM_PROJECT_PROJECTMANAGER_H
