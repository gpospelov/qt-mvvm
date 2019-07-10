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
#include "mvvm_types.h"

namespace ModelView
{

class SessionItem;

//! Command for unddo/redo to insert new item.

class CORE_EXPORT InsertNewItemCommand : public AbstractItemCommand
{
public:
    using result_t = SessionItem*;

    InsertNewItemCommand(model_type modelType, SessionItem* parent, std::string tag, int row);
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
