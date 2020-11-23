// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_UNDDOSTACKINTERFACE_H
#define MVVM_INTERFACES_UNDDOSTACKINTERFACE_H

#include <QUndoStack>

namespace ModelView
{

class UndoStackInterface : private QUndoStack
{
public:
    void push(QUndoCommand* cmd) { QUndoStack::push(cmd); }
    bool isActive() const { return QUndoStack::isActive(); }
    bool canUndo() const { return QUndoStack::canUndo(); }
    bool canRedo() const { return QUndoStack::canRedo(); }
    int index() const { return QUndoStack::index(); }
    int count() const { return QUndoStack::count(); }
    void undo() { return QUndoStack::undo(); }
    void redo() { return QUndoStack::redo(); }
    void clear() { return QUndoStack::clear(); }
    void setUndoLimit(int limit) { return QUndoStack::setUndoLimit(limit); }

    QUndoStack* qUndoStack() {
        return this;
    }
};

} // namespace ModelView

#endif // MVVM_INTERFACES_UNDDOSTACKINTERFACE_H
