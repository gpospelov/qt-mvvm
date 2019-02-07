// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COMMANDSERVICE_H
#define COMMANDSERVICE_H

#include "global.h"
#include "model_types.h"
#include <memory>

class QUndoStack;
class QUndoCommand;
class QVariant;

namespace ModelView
{

class SessionModel;
class SessionItem;

//! Provides undo/redo for all commands of SessionModel.

class CORE_EXPORT CommandService
{
public:
    CommandService(SessionModel* model);

    void setUndoRedoEnabled(bool value);

    SessionItem* insertNewItem(const model_type& modelType, SessionItem* parent, int row,
                               std::string tag);

    bool setData(SessionItem* item, const QVariant& value, int role);

    void removeAt(SessionItem* parent, int index);

    QUndoStack* undoStack() const;

    void setCommandRecordPause(bool value);

private:
    template <typename C, typename... Args> typename C::result_t process_command(Args&&... args);

    bool run_command(QUndoCommand* command);
    bool provideUndo() const;

    SessionModel* m_model;
    std::unique_ptr<QUndoStack> m_commands;
    bool m_pause_record;
};

//! Creates and processes command of given type using given argument list.

template <typename C, typename... Args>
typename C::result_t CommandService::process_command(Args&&... args)
{
    auto command = std::make_unique<C>(std::forward<Args>(args)...);

    bool was_added_to_stack = run_command(command.get());
    typename C::result_t result = command->result();

    if (was_added_to_stack)
        command.release();

    return result;
}

} // namespace ModelView

#endif // COMMANDSERVICE_H
