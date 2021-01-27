// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/factories/projectmanagerfactory.h"
#include "mvvm/project/projectmanagerdecorator.h"

namespace ModelView {
std::unique_ptr<ProjectManagerInterface>
CreateProjectManager(const ProjectContext& project_context,
                     const UserInteractionContext& user_context)
{
    return std::make_unique<ProjectManagerDecorator>(project_context, user_context);
}

} // namespace ModelView
