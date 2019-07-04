// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_REMOVEITEMCOMMAND_H
#define MVVM_REMOVEITEMCOMMAND_H

#include "abstractitemcommand.h"
#include <memory>

namespace ModelView
{

class SessionModel;
class SessionItem;
class ItemBackupStrategy;

//! Command for unddo/redo framework to remove item from a model using child's tag and row.

class CORE_EXPORT RemoveItemCommand : public AbstractItemCommand
{
public:
    using result_t = bool;

    RemoveItemCommand(SessionItem* parent, std::string tag, int row);
    ~RemoveItemCommand() override;

    void undo() override;
    void execute() override;

    result_t result() const;

private:
    std::string m_tag;
    int m_row;
    result_t m_result;
    std::unique_ptr<ItemBackupStrategy> m_backup_strategy;
};

} // namespace ModelView

#endif // MVVM_REMOVEITEMCOMMAND_H
