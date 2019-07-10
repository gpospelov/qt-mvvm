// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_INSERTITEMCOMMAND_H
#define MVVM_INSERTITEMCOMMAND_H

#include "abstractitemcommand.h"
#include "mvvm_types.h"

namespace ModelView
{

class SessionItem;

//! Command to insert new item.

class CORE_EXPORT InsertItemCommand : public AbstractItemCommand
{
public:
    using result_t = bool;

    InsertItemCommand(model_type modelType, SessionItem* parent, std::string tag, int row);
    ~InsertItemCommand() override;

    result_t result() const;

private:
    void undo_command() override;
    void execute_command() override;

    struct InsertItemCommandPrivate;
    std::unique_ptr<InsertItemCommandPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_INSERTITEMCOMMAND_H
