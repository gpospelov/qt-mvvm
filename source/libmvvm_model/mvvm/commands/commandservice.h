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

#include "mvvm/commands/commandresult.h"
#include "mvvm/core/variant.h"
#include "mvvm/interfaces/undostackinterface.h"
#include "mvvm/model/function_types.h"
#include "mvvm/model_export.h"
#include <memory>

namespace ModelView {

class SessionModel;
class SessionItem;
class TagRow;

//! Provides undo/redo for all commands of SessionModel.

class MVVM_MODEL_EXPORT CommandService {
public:
    CommandService(SessionModel* model);

    void setUndoRedoEnabled(bool value);

    SessionItem* insertNewItem(const item_factory_func_t& func, SessionItem* parent,
                               const TagRow& tagrow);

    SessionItem* copyItem(const SessionItem* item, SessionItem* parent, const TagRow& tagrow);

    bool setData(SessionItem* item, const Variant& value, int role);

    void removeItem(SessionItem* parent, const TagRow& tagrow);

    void moveItem(SessionItem* item, SessionItem* new_parent, const TagRow& tagrow);

    UndoStackInterface* undoStack() const;

    void setCommandRecordPause(bool value);

private:
    template <typename C, typename... Args> CommandResult process_command(Args&&... args);

    bool provideUndo() const;

    SessionModel* m_model;
    std::unique_ptr<UndoStackInterface> m_commands;
    bool m_pause_record;
};

//! Creates and processes command of given type using given argument list.

template <typename C, typename... Args>
CommandResult CommandService::process_command(Args&&... args)
{
    if (provideUndo()) {
        // making shared because underlying QUndoStack requires ownership
        auto command = std::make_shared<C>(std::forward<Args>(args)...);
        m_commands->execute(command);
        return command->result();
    }
    else {
        C command(std::forward<Args>(args)...);
        command.execute();
        return command.result();
    }
}

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDSERVICE_H
