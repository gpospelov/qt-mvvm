// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_VARIANT_CONSTANTS_H
#define MVVM_MODEL_VARIANT_CONSTANTS_H

#include <string>
#include <QtGlobal>

//! @file variant-constants.h
//! Collection of constants with supported variant names.

namespace ModelView::Constants {

const std::string invalid_type_name = "invalid";
const std::string bool_type_name = "bool";
const std::string int_type_name = "int";

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
const std::string string_type_name = "std::string";
#else
//! FIXME find less fragile way of deducying type of the variant
const std::string string_type_name = "std::__cxx11::basic_string<char>";
#endif

const std::string double_type_name = "double";
const std::string vector_double_type_name = "std::vector<double>";
const std::string comboproperty_type_name = "ModelView::ComboProperty";
const std::string qcolor_type_name = "QColor";
const std::string extproperty_type_name = "ModelView::ExternalProperty";
const std::string reallimits_type_name = "ModelView::RealLimits";


} // namespace ModelView::Constants

#endif // MVVM_MODEL_VARIANT_CONSTANTS_H
