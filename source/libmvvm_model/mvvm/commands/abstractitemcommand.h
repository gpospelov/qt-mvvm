// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H
#define MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H

#include "mvvm/commands/commandresult.h"
#include "mvvm/model_export.h"
#include <memory>
#include <string>

namespace ModelView {

class SessionItem;
class SessionModel;
class Path;

//! Abstract command interface to manipulate SessionItem in model context.

class MVVM_MODEL_EXPORT AbstractItemCommand {
public:
    explicit AbstractItemCommand(SessionItem* receiver);
    virtual ~AbstractItemCommand();

    AbstractItemCommand(const AbstractItemCommand& other) = delete;
    AbstractItemCommand& operator=(const AbstractItemCommand& other) = delete;

    void execute();

    void undo();

    bool isObsolete() const;

    std::string description() const;

    CommandResult result() const;

protected:
    void setObsolete(bool flag);
    void setDescription(const std::string& text);
    Path pathFromItem(SessionItem* item) const;
    SessionItem* itemFromPath(const Path& path) const;
    SessionModel* model() const;
    void setResult(const CommandResult& command_result);

private:
    virtual void execute_command() = 0;
    virtual void undo_command() = 0;

    struct AbstractItemCommandImpl;
    std::unique_ptr<AbstractItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H
