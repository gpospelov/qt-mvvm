// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_EDITORCONSTANTS_H
#define MVVM_EDITORS_EDITORCONSTANTS_H

//! @file editor_constants.h
//! Collection of constants specific for cell editing.

#include <string>

namespace ModelView
{

namespace Constants
{

const std::string BoolEditorType = "BoolEditor";
const std::string ColorEditorType = "ColorEditor";
const std::string ComboPropertyEditorType = "ComboPropertyEditor";
const std::string DoubleEditorType = "DoubleEditor";
const std::string ExternalPropertyEditorType = "ExternalPropertyEditor";
const std::string IntegerEditorType = "IntegerEditor";
const std::string ScientficDoubleEditorType = "ScientficDoubleEditor";
const std::string ScientficSpinBoxEditorType = "ScientficSpinBoxEditor";
const std::string SelectableComboPropertyEditorType = "SelectableComboPropertyEditor";

const int default_double_decimals = 4; //! number of digits after decimal points

} // namespace Constants

} // namespace ModelView

#endif // MVVM_EDITORS_EDITORCONSTANTS_H
