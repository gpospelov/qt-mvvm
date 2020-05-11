// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTMANAGERDECORATOR_H
#define PROJECTMANAGERDECORATOR_H

#include "projectmanagerinterface.h"
#include <memory>
#include <functional>

class ApplicationModelsInterface;

//! Responsible for handling new/save/save-as/close project logic, where project mean collection
//! of serialized application models in project directory.

class ProjectManagerDecorator : public ProjectManagerInterface
{
    Q_OBJECT
public:
    using selector_t = std::function<std::string()>;

    ProjectManagerDecorator(ApplicationModelsInterface* app_models, selector_t open_dir, selector_t create_dir);
    ~ProjectManagerDecorator() override;

    ProjectManagerDecorator(const ProjectManagerDecorator& other) = delete;
    ProjectManagerDecorator& operator=(const ProjectManagerDecorator& other) = delete;

    bool createNewProject(const std::string& dirname = {}) override;

    bool saveCurrentProject() override;

    bool saveProjectAs(const std::string& dirname = {}) override;

    bool openExistingProject(const std::string& dirname = {}) override;

    std::string currentProjectDir() const;

    bool isModified() const override;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

#endif // PROJECTMANAGERDECORATOR_H
