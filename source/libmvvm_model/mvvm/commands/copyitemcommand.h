// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COPYITEMCOMMAND_H
#define MVVM_COMMANDS_COPYITEMCOMMAND_H

#include "mvvm/commands/abstractitemcommand.h"

namespace ModelView {

class SessionItem;
class TagRow;

//! Command to copy an item.

class MVVM_MODEL_EXPORT CopyItemCommand : public AbstractItemCommand {
public:
    CopyItemCommand(const SessionItem* item, SessionItem* parent, TagRow tagrow);
    ~CopyItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct CopyItemCommandImpl;
    std::unique_ptr<CopyItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_COPYITEMCOMMAND_H
