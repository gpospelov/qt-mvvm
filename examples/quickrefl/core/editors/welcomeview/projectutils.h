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

#include <string>

namespace ModelView
{
class SessionModel;
}

//! Collection of utility functions to handle project saving and loading.

namespace ProjectUtils
{
std::string SuggestFileName(const ModelView::SessionModel& model);
}

#endif // PROJECTUTILS_H
