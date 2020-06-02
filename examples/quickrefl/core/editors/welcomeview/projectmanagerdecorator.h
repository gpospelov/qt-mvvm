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

#include <mvvm/interfaces/projectmanagerinterface.h>
#include <functional>
#include <memory>
#include "project_types.h"

class ApplicationModelsInterface;

//! Decorator for ProjectManager to provide interaction with the user on open/save-as requests.
//! It relies on the same interface and adds additional logic related to "unsaved" data.

//! For example, on createNewProject it will check if previous project is saved, and will
//! call external dialog save/discard/cancel via provided callback.

class ProjectManagerDecorator : public ProjectManagerInterface
{
public:
    using select_dir_callback_t = std::function<std::string()>;
    using create_dir_callback_t = std::function<std::string()>;
    using answer_callback_t = std::function<SaveChangesAnswer()>;
    using project_modified_callback_t = std::function<void()>;

    ProjectManagerDecorator(ApplicationModelsInterface* app_models,
                            select_dir_callback_t select_dir = {},
                            create_dir_callback_t create_dir = {},
                            project_modified_callback_t modified_callback = {});

    ~ProjectManagerDecorator() override;
    ProjectManagerDecorator(const ProjectManagerDecorator& other) = delete;
    ProjectManagerDecorator& operator=(const ProjectManagerDecorator& other) = delete;

    void setSelectDirCallback(select_dir_callback_t callback);

    void setCreateDirCallback(create_dir_callback_t callback);

    void setSaveChangesAnswerCallback(answer_callback_t callback);

    bool createNewProject(const std::string& dirname = {}) override;

    bool saveCurrentProject() override;

    bool saveProjectAs(const std::string& dirname = {}) override;

    bool openExistingProject(const std::string& dirname = {}) override;

    std::string currentProjectDir() const override;

    bool isModified() const override;

    bool closeCurrentProject() const override;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

#endif // PROJECTMANAGERDECORATOR_H
