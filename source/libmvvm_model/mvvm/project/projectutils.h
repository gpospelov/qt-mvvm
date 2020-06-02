// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECTUTILS_H
#define MVVM_PROJECT_PROJECTUTILS_H

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace ModelView
{
class SessionModel;
class ApplicationModelsInterface;
class ProjectInterface;

//! Collection of utility functions to handle project saving and loading.

namespace ProjectUtils
{

std::string SuggestFileName(const SessionModel& model);

bool IsPossibleProjectDir(const std::string& project_dir);

std::unique_ptr<ProjectInterface>
CreateUntitledProject(ApplicationModelsInterface* models,
                      std::function<void()> project_changed_callback = {});

std::string ProjectWindowTitle(const ProjectInterface& project);

std::string ProjectWindowTitle(const std::string& project_dir, bool is_modified);

} // namespace ProjectUtils

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTUTILS_H
