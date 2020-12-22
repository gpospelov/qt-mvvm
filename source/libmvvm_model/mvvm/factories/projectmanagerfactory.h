// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_PROJECTMANAGERFACTORY_H
#define MVVM_FACTORIES_PROJECTMANAGERFACTORY_H

#include "mvvm/interfaces/projectmanagerinterface.h"
#include <memory>

namespace ModelView {

struct ProjectContext;
struct UserInteractionContext;

//! Creates default ProjectManager to save and load models.
MVVM_MODEL_EXPORT std::unique_ptr<ProjectManagerInterface>
CreateProjectManager(const ProjectContext& project_context,
                     const UserInteractionContext& user_context);

} // namespace ModelView

#endif // MVVM_FACTORIES_PROJECTMANAGERFACTORY_H
