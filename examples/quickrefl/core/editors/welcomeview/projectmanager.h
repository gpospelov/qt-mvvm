// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include "projectmanagerinterface.h"
#include <memory>
#include <functional>

class ApplicationModelsInterface;

//! Responsible for handling new/save/save-as/close project logic, where project mean collection
//! of serialized application models in project directory.

class ProjectManager : public ProjectManagerInterface
{
    Q_OBJECT
public:
    using selector_t = std::function<std::string()>;

    ProjectManager(ApplicationModelsInterface* app_models, selector_t open_dir, selector_t create_dir);
    ~ProjectManager() override;

    ProjectManager(const ProjectManager& other) = delete;
    ProjectManager& operator=(const ProjectManager& other) = delete;

    bool createNewProject() override;

    bool saveCurrentProject() override;

    bool saveProjectAs() override;

    bool openExistingProject() override;

    std::string currentProjectDir() const;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

#endif // PROJECTMANAGER_H
