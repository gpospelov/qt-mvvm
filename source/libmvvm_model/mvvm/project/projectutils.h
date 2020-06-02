// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTUTILS_H
#define PROJECTUTILS_H

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace ModelView
{
class SessionModel;
class ApplicationModelsInterface;
class ProjectInterface;
}

//! Collection of utility functions to handle project saving and loading.

namespace ProjectUtils
{

std::string SuggestFileName(const ModelView::SessionModel& model);

bool IsPossibleProjectDir(const std::string& project_dir);

std::unique_ptr<ModelView::ProjectInterface>
CreateUntitledProject(ModelView::ApplicationModelsInterface* models,
                      std::function<void()> project_changed_callback = {});

std::string ProjectWindowTitle(const ModelView::ProjectInterface& project);

std::string ProjectWindowTitle(const std::string& project_dir, bool is_modified);

} // namespace ProjectUtils

#endif // PROJECTUTILS_H
