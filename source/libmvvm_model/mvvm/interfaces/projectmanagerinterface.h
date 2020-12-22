// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_PROJECTMANAGERINTERFACE_H
#define MVVM_INTERFACES_PROJECTMANAGERINTERFACE_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView {

//! Interface class for ProjectManager family.

//! Responsible for handling new/save/save-as/close Project logic, where the Project represents
//! a collection of serialized application models in the project directory.

class MVVM_MODEL_EXPORT ProjectManagerInterface {
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

} // namespace ModelView

#endif // MVVM_INTERFACES_PROJECTMANAGERINTERFACE_H
