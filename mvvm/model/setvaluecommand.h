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

    void undo() override;
    void execute() override;

    result_t result() const;

private:
    QVariant m_value; //! Value to set as a result of command execution.
    int m_role;
    result_t m_result;
};

}  // namespace ModelView

#endif // MVVM_SETVALUECOMMAND_H
