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
#include <QVariant>

namespace ModelView {

class SessionModel;
class SessionItem;

//! Command for unddo/redo framework to set the data of SessionItem.

class CORE_EXPORT SetValueCommand : public AbstractItemCommand
{
public:
    using result_t = bool;
    SetValueCommand(SessionItem* item, QVariant value, int role);

    result_t result() const;

private:
    void undo_command() override;
    void execute_command() override;

    QVariant m_value; //! Value to set as a result of command execution.
    int m_role;
    result_t m_result;
    Path m_item_path;
};

}  // namespace ModelView

#endif // MVVM_SETVALUECOMMAND_H
