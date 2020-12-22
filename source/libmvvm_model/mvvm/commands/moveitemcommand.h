// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_MOVEITEMCOMMAND_H
#define MVVM_COMMANDS_MOVEITEMCOMMAND_H

#include "mvvm/commands/abstractitemcommand.h"
#include <memory>

namespace ModelView {

class SessionItem;
class TagRow;

//! Command for unddo/redo framework to move item from one parent to another.

class MVVM_MODEL_EXPORT MoveItemCommand : public AbstractItemCommand {
public:
    MoveItemCommand(SessionItem* item, SessionItem* new_parent, TagRow tagrow);
    ~MoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct MoveItemCommandImpl;
    std::unique_ptr<MoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_MOVEITEMCOMMAND_H
