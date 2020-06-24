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

#include <functional>
#include <memory>
#include <mvvm/viewmodel_export.h>

namespace ModelView
{

class CustomEditor;
class SessionItem;

//! Collection of methods to build custom editors for trees/tables cells.
//! Used to edit SessionItem data in the context of DefaultEditorFactory.
namespace EditorBuilders
{

using builder_t = std::function<std::unique_ptr<CustomEditor>(const SessionItem*)>;

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

} // namespace EditorBuilders

} // namespace ModelView

#endif // MVVM_EDITORS_EDITORBUILDERS_H
