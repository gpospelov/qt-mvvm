// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_MOVEITEMCOMMAND_H
#define MVVM_MOVEITEMCOMMAND_H

#include "abstractitemcommand.h"
#include <memory>

namespace ModelView
{

class SessionItem;
class TagRow;

//! Command for unddo/redo framework to move item from one parent to another.

class CORE_EXPORT MoveItemCommand : public AbstractItemCommand
{
public:
    using result_t = bool;

    MoveItemCommand(SessionItem* item, SessionItem* new_parent, TagRow tagrow);
    ~MoveItemCommand() override;

    result_t result() const;

private:
    void undo_command() override;
    void execute_command() override;

    struct MoveItemCommandImpl;
    std::unique_ptr<MoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_MOVEITEMCOMMAND_H
