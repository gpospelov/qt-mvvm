// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "commandservice.h"
#include "copyitemcommand.h"
#include "insertnewitemcommand.h"
#include "moveitemcommand.h"
#include "removeitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "setvaluecommand.h"
#include <QUndoStack>

using namespace ModelView;

CommandService::CommandService(SessionModel* model) : m_model(model), m_pause_record(false) {}

void CommandService::setUndoRedoEnabled(bool value)
{
    if (value)
        m_commands = std::make_unique<QUndoStack>();
    else
        m_commands.reset();
}

SessionItem* CommandService::insertNewItem(item_factory_func_t func, SessionItem* parent,
                                           std::string tag, int row)
{
    if (!parent)
        parent = m_model->rootItem();

    return process_command<InsertNewItemCommand>(func, parent, tag, row);
}

SessionItem* CommandService::copyItem(const SessionItem* item, SessionItem* parent,
                                      const std::string& tag, int row)
{
    if (!item)
        return nullptr;

    if (parent->model() != m_model)
        throw std::runtime_error(
            "CommandService::copyItem() -> Item doesn't belong to given model");

    return process_command<CopyItemCommand>(item, parent, tag, row);
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

void CommandService::moveItem(SessionItem* item, SessionItem* new_parent, const std::string& tag,
                              int row)
{
    if (item->model() != m_model)
        throw std::runtime_error(
            "CommandService::removeRow() -> Item doesn't belong to given model");

    if (new_parent->model() != m_model)
        throw std::runtime_error(
            "CommandService::removeRow() -> Parent doesn't belong to given model");

    process_command<MoveItemCommand>(item, new_parent, tag, row);
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
    return m_commands && !m_pause_record;
}
