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

#include <memory>
#include <string>
#include <vector>

namespace ModelView
{
class SessionModel;
}

class ProjectInterface;
class ApplicationModelsInterface;

//! Collection of utility functions to handle project saving and loading.

namespace ProjectUtils
{

std::string SuggestFileName(const ModelView::SessionModel& model);

std::unique_ptr<ProjectInterface> CreateUntitledProject(ApplicationModelsInterface* models);

} // namespace ProjectUtils

#endif // PROJECTUTILS_H
