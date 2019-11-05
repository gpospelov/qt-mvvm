// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_STRINGUTILS_H
#define MVVM_STRINGUTILS_H

#include <mvvm/model/mvvm_export.h>
#include <string>

namespace ModelView
{

namespace Utils
{

//! Returns string representation of double with given precision.
CORE_EXPORT std::string DoubleToString(double input, int precision = 12);

//! Returns string representation of scientific double
CORE_EXPORT std::string ScientificDoubleToString(double input, int precision = 6);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_STRINGUTILS_H
