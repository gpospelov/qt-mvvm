// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COMMANDADAPTER_H
#define MVVM_COMMANDS_COMMANDADAPTER_H

#include <mvvm/core/export.h>
#include <QUndoCommand>
#include <memory>

namespace ModelView
{

class AbstractItemCommand;

//! Adapter to execute our commands within Qt undo/redo framework.

class CORE_EXPORT CommandAdapter : public QUndoCommand
{
public:
    CommandAdapter(std::shared_ptr<AbstractItemCommand> command);
    ~CommandAdapter() override;

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<AbstractItemCommand> m_command;
};

} // namespace ModelView

#endif  // MVVM_COMMANDS_COMMANDADAPTER_H
