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
#include "sessionmodel.h"
#include "sessionitem.h"
#include <QUndoStack>

CommandService::CommandService(SessionModel* model)
    : m_model(model)
{

}

void CommandService::setUndoRedoEnabled(bool value)
{
    if (value)
        m_commands.reset(new QUndoStack);
    else
        m_commands.reset();
}

void CommandService::push(QUndoCommand* command)
{
    if (provideUndo()) {
        m_commands->push(command);
    } else {
        command->redo();
        delete command;
    }
}

SessionItem* CommandService::insertNewItem(const model_type& modelType, SessionItem* parent, int row)
{
    if (!parent)
        parent = m_model->rootItem();

    // FIXME when tag is there
    row = row < 0 ? parent->childrenCount() : row;

    push(new InsertNewItemCommand(modelType, parent, row));

    return parent->childAt(row);
}

bool CommandService::setData(SessionItem* item, const QVariant& value, int role)
{
    if (!item)
        return false;

    push(new SetValueCommand(item, value, role));

    return true;
}

void CommandService::removeRow(SessionItem* parent, int row)
{
    if (parent->model() != m_model)
        throw std::runtime_error("CommandService::removeRow() -> Item doesn't belong to given model");

    push(new RemoveRowCommand(parent, row));
}

QUndoStack* CommandService::undoStack() const
{
    return m_commands.get();
}

void CommandService::setCommandRecordPause(bool value)
{
    m_pause_record = value;
}

bool CommandService::provideUndo() const
{
    return m_commands && !m_pause_record ? true : false;
}
