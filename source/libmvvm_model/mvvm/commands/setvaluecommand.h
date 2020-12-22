// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_SETVALUECOMMAND_H
#define MVVM_COMMANDS_SETVALUECOMMAND_H

#include "mvvm/commands/abstractitemcommand.h"
#include "mvvm/core/variant.h"

namespace ModelView {

class SessionItem;

//! Command for unddo/redo framework to set the data of SessionItem.

class MVVM_MODEL_EXPORT SetValueCommand : public AbstractItemCommand {
public:
    SetValueCommand(SessionItem* item, Variant value, int role);
    ~SetValueCommand() override;

private:
    void undo_command() override;
    void execute_command() override;
    void swap_values();

    struct SetValueCommandImpl;
    std::unique_ptr<SetValueCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_SETVALUECOMMAND_H
