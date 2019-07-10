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

class SessionModel;
class SessionItem;

//! Command for unddo/redo framework to move item from one parent to another.

class CORE_EXPORT MoveItemCommand : public AbstractItemCommand
{
public:
    using result_t = bool;

    MoveItemCommand(SessionItem* item, SessionItem* new_parent, const std::string& tag, int row);

    void undo() override;
    void execute() override;

    result_t result() const;

private:
    std::string m_target_tag;
    int m_target_row;
    Path m_target_parent_path;
    Path m_original_parent_path;
    std::string m_original_tag;
    int m_original_row;
    result_t m_result;
};

} // namespace ModelView

#endif // MVVM_MOVEITEMCOMMAND_H
