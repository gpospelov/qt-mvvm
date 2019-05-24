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

#include "editorfactoryinterface.h"
#include <memory>
#include <functional>

namespace ModelView
{

class CustomEditor;
class SessionItem;

//! Collection of methods to build custom editors for trees/tables cells.
//! Used to edit SessionItem data in the context of DefaultEditorFactory.
namespace EditorBuilders {

using builder_t = std::function<std::unique_ptr<CustomEditor>(const SessionItem*)>;

//! Constructor for simple double editor based on usual spin box with limits.
//CORE_EXPORT strategy_t DefaultDoubleEditorConstructor();

//! Constructor for double editor with scientific notation.
CORE_EXPORT builder_t ScientificDoubleEditorBuilder();

}

} // namespace ModelView

#endif // MVVM_EDITORBUILDERSTRATEGY_H
