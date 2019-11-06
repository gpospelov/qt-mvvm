// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H
#define MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H

#include <mvvm/core/export.h>
#include <mvvm/model/path.h>
#include <memory>
#include <string>

namespace ModelView
{

class SessionItem;
class SessionModel;

//! Abstract command interface to manipulate SessionItem in model context.

class CORE_EXPORT AbstractItemCommand
{
public:
    explicit AbstractItemCommand(SessionItem* receiver);
    virtual ~AbstractItemCommand();

    void execute();

    void undo();

    bool isObsolete() const;

    std::string description() const;

protected:
    void setObsolete(bool flag);
    void setDescription(const std::string& text);
    Path pathFromItem(SessionItem* item) const;
    SessionItem* itemFromPath(Path path) const;
    SessionModel* model() const;

private:
    virtual void execute_command() = 0;
    virtual void undo_command() = 0;

    struct AbstractItemCommandImpl;
    std::unique_ptr<AbstractItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H
