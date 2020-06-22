// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_REMOVEITEMCOMMAND_H
#define MVVM_COMMANDS_REMOVEITEMCOMMAND_H

#include <mvvm/commands/abstractitemcommand.h>

namespace ModelView
{

class SessionItem;
class TagRow;

//! Command for unddo/redo framework to remove item from a model using child's tag and row.

class MVVM_MODEL_EXPORT RemoveItemCommand : public AbstractItemCommand
{
public:
    using result_t = bool;

    RemoveItemCommand(SessionItem* parent, TagRow tagrow);
    ~RemoveItemCommand() override;

    result_t result() const;

private:
    void undo_command() override;
    void execute_command() override;

    struct RemoveItemCommandImpl;
    std::unique_ptr<RemoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_REMOVEITEMCOMMAND_H
