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

#include "mvvm/model_export.h"
#include <memory>
#include <string>

namespace ModelView {

class SessionModel;
class ProjectInterface;
struct ProjectContext;

//! Collection of utility functions to handle project saving and loading.

namespace ProjectUtils {

MVVM_MODEL_EXPORT std::string SuggestFileName(const SessionModel& model);

MVVM_MODEL_EXPORT bool IsPossibleProjectDir(const std::string& project_dir);

MVVM_MODEL_EXPORT std::unique_ptr<ProjectInterface>
CreateUntitledProject(const ProjectContext& context);

MVVM_MODEL_EXPORT std::string ProjectWindowTitle(const ProjectInterface& project);

MVVM_MODEL_EXPORT std::string ProjectWindowTitle(const std::string& project_dir, bool is_modified);

} // namespace ProjectUtils

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTUTILS_H
