// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QUndoStack>
#include <mvvm/commands/undostack.h>

using namespace ModelView;

struct UndoStack::UndoStackImpl {
    std::unique_ptr<QUndoStack> m_undoStack;
    UndoStackImpl() : m_undoStack(std::make_unique<QUndoStack>()) {}
    QUndoStack* stack() { return m_undoStack.get(); }
};

UndoStack::UndoStack() : p_impl(std::make_unique<UndoStackImpl>()) {}

UndoStack::~UndoStack() = default;

void UndoStack::push(QUndoCommand* cmd)
{
    p_impl->stack()->push(cmd);
}

bool UndoStack::isActive() const
{
    return p_impl->stack()->isActive();
}

bool UndoStack::canUndo() const
{
    return p_impl->stack()->canUndo();
}

bool UndoStack::canRedo() const
{
    return p_impl->stack()->canRedo();
}

int UndoStack::index() const
{
    return p_impl->stack()->index();
}

int UndoStack::count() const
{
    return p_impl->stack()->count();
}

void UndoStack::undo()
{
    return p_impl->stack()->undo();
}

void UndoStack::redo()
{
    return p_impl->stack()->redo();
}

void UndoStack::clear()
{
    return p_impl->stack()->clear();
}

void UndoStack::setUndoLimit(int limit)
{
    return p_impl->stack()->setUndoLimit(limit);
}

//! Returns underlying QUndoStack if given object can be casted to UndoStack instance.

QUndoStack* UndoStack::qtUndoStack(UndoStackInterface* stack_interface)
{
    if (auto stack = dynamic_cast<UndoStack*>(stack_interface); stack)
        return stack->p_impl->stack();
    return nullptr;
}
