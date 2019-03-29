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
#include <QUndoStack>

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

    SessionItem* insertNewItem(const model_type& modelType, SessionItem* parent, std::string tag, int row);

    bool setData(SessionItem* item, const QVariant& value, int role);

    void removeItem(SessionItem* parent, const std::string& tag, int row);

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

    // FIXME replace logic below with shared_ptr
    typename C::result_t result;
    if (provideUndo()) {
        m_commands->push(command.get());
        if (m_commands->count() && (m_commands->command(m_commands->count()-1) == command.get()))
            result = command->result();
        command.release();
    } else {
        command->redo();
        result = command->result();
    }

    return result;
}

} // namespace ModelView

#endif // COMMANDSERVICE_H
