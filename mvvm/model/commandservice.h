// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COMMANDSERVICE_H
#define MVVM_COMMANDSERVICE_H

#include "mvvm_global.h"
#include "mvvm_types.h"
#include "commandadapter.h"
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

    void moveItem(SessionItem* item, SessionItem* new_parent, const std::string& tag, int row);

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

#endif // MVVM_COMMANDSERVICE_H
