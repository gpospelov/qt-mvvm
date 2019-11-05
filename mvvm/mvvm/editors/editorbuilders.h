// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_EDITORBUILDERSTRATEGY_H
#define MVVM_EDITORBUILDERSTRATEGY_H

#include <mvvm/editors/editorfactoryinterface.h>
#include <functional>
#include <memory>

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
CORE_EXPORT builder_t BoolEditorBuilder();

//! Builder for integer property editor.
CORE_EXPORT builder_t IntegerEditorBuilder();

//! Builder for double editor with limits support.
CORE_EXPORT builder_t DoubleEditorBuilder();

//! Builder for double editor with scientific notation based on simple text field.
CORE_EXPORT builder_t ScientificDoubleEditorBuilder();

//! Builder for double editor with scientific notation and spinbox functionality.
CORE_EXPORT builder_t ScientificSpinBoxEditorBuilder();

//! Builder for color property editor.
CORE_EXPORT builder_t ColorEditorBuilder();

//! Builder for ComboProperty editor.
CORE_EXPORT builder_t ComboPropertyEditorBuilder();

//! Builder for external property editor.
CORE_EXPORT builder_t ExternalPropertyEditorBuilder();

} // namespace EditorBuilders

} // namespace ModelView

#endif // MVVM_EDITORBUILDERSTRATEGY_H
