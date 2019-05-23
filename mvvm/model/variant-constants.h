// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_MVVM_TYPES_H
#define MVVM_MVVM_TYPES_H

#include <string>

//! @file variant-constants.h
//! Collection of constants with supported variant names.

namespace ModelView
{
namespace Constants
{

const std::string invalid_type_name = "invalid";
const std::string int_type_name = "int";
const std::string string_type_name = "std::string";
const std::string double_type_name = "double";
const std::string vector_double_type_name = "std::vector<double>";
const std::string comboproperty_type_name = "ModelView::ComboProperty";
const std::string qcolor_type_name = "QColor";
const std::string extproperty_type_name = "ModelView::ExternalProperty";
const std::string reallimits_type_name = "ModelView::RealLimits";

} // namespace Constants

} // namespace ModelView

#endif // MVVM_MVVM_TYPES_H
