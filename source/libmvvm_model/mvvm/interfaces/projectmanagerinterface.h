// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTMANAGERINTERFACE_H
#define PROJECTMANAGERINTERFACE_H

#include <mvvm/core/export.h>
#include <string>

//! Interface class for ProjectManager family.

//! Responsible for handling new/save/save-as/close Project logic, where the Project represents
//! a collection of serialized application models in the project directory.

class CORE_EXPORT ProjectManagerInterface
{
public:
    virtual ~ProjectManagerInterface() = default;
    virtual bool createNewProject(const std::string& dirname = {}) = 0;

    virtual bool saveCurrentProject() = 0;

    virtual bool saveProjectAs(const std::string& dirname = {}) = 0;

    virtual bool openExistingProject(const std::string& dirname = {}) = 0;

    virtual std::string currentProjectDir() const = 0;

    virtual bool isModified() const = 0;

    virtual bool closeCurrentProject() const = 0;
};

#endif // PROJECTMANAGERINTERFACE_H
