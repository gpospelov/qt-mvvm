// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_INSERTNEWITEMCOMMAND_H
#define MVVM_INSERTNEWITEMCOMMAND_H

#include "abstractitemcommand.h"
#include "function_types.h"

namespace ModelView
{

class SessionItem;
class TagRow;

//! Command for unddo/redo to insert new item.

class CORE_EXPORT InsertNewItemCommand : public AbstractItemCommand
{
public:
    using result_t = SessionItem*;

    InsertNewItemCommand(item_factory_func_t func, SessionItem* parent, TagRow tagrow);
    ~InsertNewItemCommand() override;

    result_t result() const;

private:
    void undo_command() override;
    void execute_command() override;

    struct InsertNewItemCommandPrivate;
    std::unique_ptr<InsertNewItemCommandPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_INSERTNEWITEMCOMMAND_H
