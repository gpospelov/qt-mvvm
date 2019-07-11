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

//! Command to copy an item.

class CORE_EXPORT CopyItemCommand : public AbstractItemCommand
{
public:
    using result_t = bool;

    CopyItemCommand(model_type modelType, SessionItem* parent, std::string tag, int row);
    ~CopyItemCommand() override;

    result_t result() const;

private:
    void undo_command() override;
    void execute_command() override;

    struct InsertItemCommandPrivate;
    std::unique_ptr<InsertItemCommandPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_COPYITEMCOMMAND_H
