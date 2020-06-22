// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_STRINGUTILS_H
#define MVVM_UTILS_STRINGUTILS_H

#include <mvvm/core/export.h>
#include <string>

namespace ModelView
{

namespace Utils
{

//! Returns string representation of double with given precision.
MVVM_MODEL_EXPORT std::string DoubleToString(double input, int precision = 12);

//! Returns string representation of scientific double
MVVM_MODEL_EXPORT std::string ScientificDoubleToString(double input, int precision = 6);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_UTILS_STRINGUTILS_H
