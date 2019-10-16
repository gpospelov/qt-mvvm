// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COPYITEMCOMMAND_H
#define MVVM_COPYITEMCOMMAND_H

#include "abstractitemcommand.h"
#include "mvvm_types.h"

namespace ModelView
{

class SessionItem;
class TagRow;

//! Command to copy an item.

class CORE_EXPORT CopyItemCommand : public AbstractItemCommand
{
public:
    using result_t = SessionItem*;

    CopyItemCommand(const SessionItem* item, SessionItem* parent, TagRow tagrow);
    ~CopyItemCommand() override;

    result_t result() const;

private:
    void undo_command() override;
    void execute_command() override;

    struct CopyItemCommandPrivate;
    std::unique_ptr<CopyItemCommandPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_COPYITEMCOMMAND_H
