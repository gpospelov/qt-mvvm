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

class ApplicationModelsInterface;

//! Responsible for handling new/save/save-as/close project logic, where project mean collection
//! of serialized application models in project directory.

class ProjectManager : public ProjectManagerInterface
{
    Q_OBJECT
public:
    ProjectManager(ApplicationModelsInterface* app_models);
    ~ProjectManager() override;

    void createNewProject() override;

    void saveCurrentProject() override;

    void saveProjectAs() override;

    void openExistingProject() override;

    std::string currentProjectDir() const;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

#endif // PROJECTMANAGER_H
