// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SETVALUECOMMAND_H
#define MVVM_SETVALUECOMMAND_H

#include "abstractitemcommand.h"

class QVariant;

namespace ModelView
{

class SessionItem;

//! Command for unddo/redo framework to set the data of SessionItem.

class CORE_EXPORT SetValueCommand : public AbstractItemCommand
{
public:
    using result_t = bool;
    SetValueCommand(SessionItem* item, QVariant value, int role);
    ~SetValueCommand() override;

    result_t result() const;

private:
    void undo_command() override;
    void execute_command() override;
    void swap_values();

    struct SetValueCommandPrivate;
    std::unique_ptr<SetValueCommandPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_SETVALUECOMMAND_H
