// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "commandservice.h"
#include "commands.h"
#include "removeitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <QUndoStack>

using namespace ModelView;

CommandService::CommandService(SessionModel* model) : m_model(model), m_pause_record(false)
{
}

void CommandService::setUndoRedoEnabled(bool value)
{
    if (value)
        m_commands = std::make_unique<QUndoStack>();
    else
        m_commands.reset();
}

SessionItem* CommandService::insertNewItem(const model_type& modelType, SessionItem* parent,
                                           std::string tag, int row)
{
    if (!parent)
        parent = m_model->rootItem();

    return process_command<InsertNewItemCommand>(modelType, parent, tag, row);
}

bool CommandService::setData(SessionItem* item, const QVariant& value, int role)
{
    if (!item)
        return false;

    return process_command<SetValueCommand>(item, value, role);
}

void CommandService::removeItem(SessionItem* parent, const std::string& tag, int row)
{
    if (parent->model() != m_model)
        throw std::runtime_error(
            "CommandService::removeRow() -> Item doesn't belong to given model");

    process_command<RemoveItemCommand>(parent, tag, row);
}

QUndoStack* CommandService::undoStack() const
{
    return m_commands.get();
}

void CommandService::setCommandRecordPause(bool value)
{
    m_pause_record = value;
}

//! Runs command by pushing it in undo/redo stack if stack is active, or executing it directly.
//! Returns true if command was added to the stack.

bool CommandService::run_command(QUndoCommand* command)
{
    if (provideUndo()) {
        m_commands->push(command); // command will be executed by stack
        return true;
    }

    command->redo();
    return false;
}

bool CommandService::provideUndo() const
{
    return m_commands && !m_pause_record;
}
