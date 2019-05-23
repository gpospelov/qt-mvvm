// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_EDITORCONSTRUCTORSTRATEGY_H
#define MVVM_EDITORCONSTRUCTORSTRATEGY_H

#include "editorfactoryinterface.h"
#include <memory>
#include <functional>

namespace ModelView
{

class CustomEditor;
class SessionItem;

//! Collection of methods to construct custom editors for trees/tables cells.
//! Used to edit SessionItem data in the context of DefaultEditorFactory.
namespace EditorConstructorStrategy {

using strategy_t = std::function<std::unique_ptr<CustomEditor>(const SessionItem*)>;

//! Constructor for simple double editor based on usual spin box with limits.
//CORE_EXPORT strategy_t DefaultDoubleEditorConstructor();

//! Constructor for double editor with scientific notation.
CORE_EXPORT strategy_t ScientificDoubleEditorConstructor();

}

} // namespace ModelView

#endif // MVVM_EDITORCONSTRUCTORSTRATEGY_H
