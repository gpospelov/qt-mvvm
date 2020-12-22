// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_EDITORBUILDERS_H
#define MVVM_EDITORS_EDITORBUILDERS_H

#include "mvvm/viewmodel_export.h"
#include <functional>
#include <memory>

namespace ModelView {

class CustomEditor;
class SessionItem;

//! Collection of methods to build custom editors for trees/tables cells.
//! Used to edit SessionItem data in the context of DefaultEditorFactory.

namespace EditorBuilders {

using editor_t = std::unique_ptr<CustomEditor>;
using builder_t = std::function<editor_t(const SessionItem*)>;

//! Builder for boolean property editor.
MVVM_VIEWMODEL_EXPORT builder_t BoolEditorBuilder();

//! Builder for integer property editor.
MVVM_VIEWMODEL_EXPORT builder_t IntegerEditorBuilder();

//! Builder for double editor with limits support.
MVVM_VIEWMODEL_EXPORT builder_t DoubleEditorBuilder();

//! Builder for double editor with scientific notation based on simple text field.
MVVM_VIEWMODEL_EXPORT builder_t ScientificDoubleEditorBuilder();

//! Builder for double editor with scientific notation and spinbox functionality.
MVVM_VIEWMODEL_EXPORT builder_t ScientificSpinBoxEditorBuilder();

//! Builder for color property editor.
MVVM_VIEWMODEL_EXPORT builder_t ColorEditorBuilder();

//! Builder for ComboProperty editor.
MVVM_VIEWMODEL_EXPORT builder_t ComboPropertyEditorBuilder();

//! Builder for external property editor.
MVVM_VIEWMODEL_EXPORT builder_t ExternalPropertyEditorBuilder();

//! Builder for ComboProperty editor with multi-selection functionality.
MVVM_VIEWMODEL_EXPORT builder_t SelectableComboPropertyEditorBuilder();

} // namespace EditorBuilders

} // namespace ModelView

#endif // MVVM_EDITORS_EDITORBUILDERS_H
