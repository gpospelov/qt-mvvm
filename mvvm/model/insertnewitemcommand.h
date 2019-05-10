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
#include "path.h"

namespace ModelView {

class SessionModel;
class SessionItem;

//! Command for unddo/redo to insert new item.

class CORE_EXPORT InsertNewItemCommand : public AbstractItemCommand
{
public:
    using result_t = SessionItem*;

    InsertNewItemCommand(model_type modelType, SessionItem* parent, std::string tag, int row);

    void undo() override;
    void redo() override;

    result_t result() const;

private:
    Path m_parent_path;
    std::string m_tag;
    int m_row;
    model_type m_model_type;
    SessionModel* m_model;
    result_t m_result;
};

}  // namespace ModelView

#endif // MVVM_INSERTNEWITEMCOMMAND_H
