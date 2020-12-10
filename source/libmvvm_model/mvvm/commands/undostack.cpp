// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QUndoStack>
#include <mvvm/commands/commandadapter.h>
#include <mvvm/commands/undostack.h>

using namespace ModelView;

struct UndoStack::UndoStackImpl {
    std::unique_ptr<QUndoStack> m_undoStack;
    UndoStackImpl() : m_undoStack(std::make_unique<QUndoStack>()) {}
    QUndoStack* undoStack() { return m_undoStack.get(); }
};

UndoStack::UndoStack() : p_impl(std::make_unique<UndoStackImpl>()) {}

void UndoStack::execute(std::shared_ptr<AbstractItemCommand> command)
{
    // Wrapping command for Qt. It will be executed by Qt after push.
    auto adapter = new CommandAdapter(std::move(command));
    p_impl->undoStack()->push(adapter);
}

UndoStack::~UndoStack() = default;

bool UndoStack::isActive() const
{
    return p_impl->undoStack()->isActive();
}

bool UndoStack::canUndo() const
{
    return p_impl->undoStack()->canUndo();
}

bool UndoStack::canRedo() const
{
    return p_impl->undoStack()->canRedo();
}

int UndoStack::index() const
{
    return p_impl->undoStack()->index();
}

int UndoStack::count() const
{
    return p_impl->undoStack()->count();
}

void UndoStack::undo()
{
    return p_impl->undoStack()->undo();
}

void UndoStack::redo()
{
    return p_impl->undoStack()->redo();
}

void UndoStack::clear()
{
    return p_impl->undoStack()->clear();
}

void UndoStack::setUndoLimit(int limit)
{
    return p_impl->undoStack()->setUndoLimit(limit);
}

//! Returns underlying QUndoStack if given object can be casted to UndoStack instance.
//! This method is used to "convert" current instance to Qt implementation, and use it with other
//! Qt widgets, if necessary.

QUndoStack* UndoStack::qtUndoStack(UndoStackInterface* stack_interface)
{
    if (auto stack = dynamic_cast<UndoStack*>(stack_interface); stack)
        return stack->p_impl->undoStack();
    return nullptr;
}

void UndoStack::beginMacro(const std::string& name)
{
    p_impl->undoStack()->beginMacro(QString::fromStdString(name));
}

void UndoStack::endMacro()
{
    p_impl->undoStack()->endMacro();
}
