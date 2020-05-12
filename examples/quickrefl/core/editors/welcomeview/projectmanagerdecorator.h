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
#include <functional>
#include <memory>

class ApplicationModelsInterface;

//! Decorator for ProjectManager to provide interaction with the user on open/save-as requests.
//! It relies on the same interface and adds additional logic related to "unsaved" data.

//! For example, on createNewProject it will check if previous project is saved, and will
//! call external dialog save/discard/cancel via provided callback.

class ProjectManagerDecorator : public ProjectManagerInterface
{
    Q_OBJECT
public:
    enum SaveChangesAnswer { SAVE = 0, DISCARD = 1, CANCEL = 2 };
    using select_dir_callback_t = std::function<std::string()>;
    using create_dir_callback_t = std::function<std::string()>;
    using answer_callback_t = std::function<SaveChangesAnswer()>;

    ProjectManagerDecorator(ApplicationModelsInterface* app_models,
                            select_dir_callback_t select_dir = {},
                            create_dir_callback_t create_dir = {});

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

    std::string currentProjectDir() const;

    bool isModified() const override;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

#endif // PROJECTMANAGERDECORATOR_H
