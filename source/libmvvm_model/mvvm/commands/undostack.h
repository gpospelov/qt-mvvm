// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_UNDOSTACK_H
#define MVVM_COMMANDS_UNDOSTACK_H

#include <mvvm/model_export.h>
#include <mvvm/interfaces/undostackinterface.h>

namespace ModelView
{

//! Default undo stack implementation (rely on QUndoStack).
//! It is implemented a) to hide Qt usage b) to simplify future refactoring toward Qt-independent
//! libmvvm_model library.

class MVVM_MODEL_EXPORT UndoStack : public UndoStackInterface
{
};

} // namespace ModelView

#endif // MVVM_COMMANDS_UNDOSTACK_H
