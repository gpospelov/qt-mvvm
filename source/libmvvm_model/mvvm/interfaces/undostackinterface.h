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

class QUndoStack;
class QUndoCommand;

namespace ModelView
{

class UndoStackInterface
{
public:
    virtual ~UndoStackInterface() = default;
    virtual void push(QUndoCommand* cmd) = 0;
    virtual bool isActive() const = 0;
    virtual bool canUndo() const  = 0;
    virtual bool canRedo() const  = 0;
    virtual int index() const  = 0;
    virtual int count() const  = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void clear() = 0;
    virtual void setUndoLimit(int limit) = 0;
    virtual QUndoStack* qUndoStack() = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_UNDDOSTACKINTERFACE_H
