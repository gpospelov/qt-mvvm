// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COMMANDSERVICE_H
#define MVVM_COMMANDS_COMMANDSERVICE_H

#include <memory>
#include <mvvm/commands/commandadapter.h>
#include <mvvm/commands/undostack.h>
#include <mvvm/core/variant.h>
#include <mvvm/model/function_types.h>
#include <mvvm/model_export.h>

class QUndoCommand;

namespace ModelView
{

class SessionModel;
class SessionItem;
class TagRow;

//! Provides undo/redo for all commands of SessionModel.

class MVVM_MODEL_EXPORT CommandService
{
public:
    CommandService(SessionModel* model);

    void setUndoRedoEnabled(bool value);

    SessionItem* insertNewItem(const item_factory_func_t& func, SessionItem* parent,
                               const TagRow& tagrow);

    SessionItem* copyItem(const SessionItem* item, SessionItem* parent, const TagRow& tagrow);

    bool setData(SessionItem* item, const Variant& value, int role);

    void removeItem(SessionItem* parent, const TagRow& tagrow);

    void moveItem(SessionItem* item, SessionItem* new_parent, const TagRow& tagrow);

    QUndoStack* undoStack() const;

    void setCommandRecordPause(bool value);

private:
    template <typename C, typename... Args> typename C::result_t process_command(Args&&... args);

    bool provideUndo() const;

    SessionModel* m_model;
    std::unique_ptr<QUndoStack> m_commands;
    bool m_pause_record;
};

//! Creates and processes command of given type using given argument list.

template <typename C, typename... Args>
typename C::result_t CommandService::process_command(Args&&... args)
{
    typename C::result_t result;

    if (provideUndo()) {
        auto command = std::make_shared<C>(std::forward<Args>(args)...);
        auto adapter = new CommandAdapter(command);
        m_commands->push(adapter);
        result = command->result();
    } else {
        auto command = std::make_unique<C>(std::forward<Args>(args)...);
        command->execute();
        result = command->result();
    }

    return result;
}

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDSERVICE_H
