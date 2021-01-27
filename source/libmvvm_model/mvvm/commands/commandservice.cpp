// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/commandservice.h"
#include "mvvm/commands/copyitemcommand.h"
#include "mvvm/commands/insertnewitemcommand.h"
#include "mvvm/commands/moveitemcommand.h"
#include "mvvm/commands/removeitemcommand.h"
#include "mvvm/commands/setvaluecommand.h"
#include "mvvm/commands/undostack.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include <stdexcept>

using namespace ModelView;

CommandService::CommandService(SessionModel* model) : m_model(model), m_pause_record(false) {}

void CommandService::setUndoRedoEnabled(bool value)
{
    if (value)
        m_commands = std::make_unique<UndoStack>();
    else
        m_commands.reset();
}

SessionItem* CommandService::insertNewItem(const item_factory_func_t& func, SessionItem* parent,
                                           const TagRow& tagrow)
{
    if (!parent)
        parent = m_model->rootItem();

    int actual_row = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    return std::get<SessionItem*>(
        process_command<InsertNewItemCommand>(func, parent, TagRow{tagrow.tag, actual_row}));
}

SessionItem* CommandService::copyItem(const SessionItem* item, SessionItem* parent,
                                      const TagRow& tagrow)
{
    if (!item)
        return nullptr;

    if (parent->model() != m_model)
        throw std::runtime_error(
            "CommandService::copyItem() -> Item doesn't belong to given model");

    int actual_row = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    return std::get<SessionItem*>(
        process_command<CopyItemCommand>(item, parent, TagRow{tagrow.tag, actual_row}));
}

bool CommandService::setData(SessionItem* item, const Variant& value, int role)
{
    if (!item)
        return false;

    return std::get<bool>(process_command<SetValueCommand>(item, value, role));
}

void CommandService::removeItem(SessionItem* parent, const TagRow& tagrow)
{
    if (parent->model() != m_model)
        throw std::runtime_error(
            "CommandService::removeRow() -> Item doesn't belong to given model");

    process_command<RemoveItemCommand>(parent, tagrow);
}

void CommandService::moveItem(SessionItem* item, SessionItem* new_parent, const TagRow& tagrow)
{
    if (item->model() != m_model)
        throw std::runtime_error(
            "CommandService::removeRow() -> Item doesn't belong to given model");

    if (new_parent->model() != m_model)
        throw std::runtime_error(
            "CommandService::removeRow() -> Parent doesn't belong to given model");

    int actual_row = tagrow.row < 0 ? new_parent->itemCount(tagrow.tag) : tagrow.row;

    process_command<MoveItemCommand>(item, new_parent, TagRow{tagrow.tag, actual_row});
}

UndoStackInterface* CommandService::undoStack() const
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
