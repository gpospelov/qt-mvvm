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

#include "mvvm/model_export.h"
#include <optional>
#include <string>
#include <vector>

namespace ModelView::Utils {

//! Returns string representation of double with given precision.
//! Provides additional formatting on top of iomanip, so "double x{0}" becomes "0.0".
MVVM_MODEL_EXPORT std::string DoubleToString(double input, int precision = 12);

//! Returns string representation of scientific double.
//! Provides additional formatting on top of iomanip, so "double x{1}" becomes "1.0e+00".
MVVM_MODEL_EXPORT std::string ScientificDoubleToString(double input, int precision = 6);

//! Returns string after trimming whitespace surrounding, including tabs and carriage returns.
MVVM_MODEL_EXPORT std::string TrimWhitespace(const std::string& str);

//! Removes repeating spaces for a string.
MVVM_MODEL_EXPORT std::string RemoveRepeatedSpaces(std::string str);

//! Converts string to double value using classc locale and returns it in the form of optional.
//! Requires that string represents exactly one double and contains no other literals. Empty
//! spaces at the beginning and end of the string are still allowed.
MVVM_MODEL_EXPORT std::optional<double> StringToDouble(const std::string& str);

//! Converts string to integer. Requires that string represents exactly one integer and
//! no extra symbols are defined. Empty spaces at the beginning and end of the string are still
//! allowed.
MVVM_MODEL_EXPORT std::optional<int> StringToInteger(const std::string& str);

//! Split string on substring using given delimeter. Reproduces Python's str.split() behavior.
MVVM_MODEL_EXPORT std::vector<std::string> SplitString(const std::string& str,
                                                       const std::string& delimeter);

//! Parses string for double values and returns result as a vector.
//! All non-numeric symbols are ingored.
MVVM_MODEL_EXPORT std::vector<double> ParseSpaceSeparatedDoubles(const std::string& str);

//! Parses string for double values and stores result in a vector.
//! All non-numeric symbols are ingored.
MVVM_MODEL_EXPORT void ParseSpaceSeparatedDoubles(const std::string& str,
                                                  std::vector<double>& result);

} // namespace ModelView::Utils

#endif // MVVM_UTILS_STRINGUTILS_H
