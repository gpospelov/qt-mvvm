// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ABSTRACTITEMCOMMAND_H
#define MVVM_ABSTRACTITEMCOMMAND_H

#include "mvvm_global.h"
#include "path.h"
#include <string>

namespace ModelView
{

class SessionItem;
class SessionModel;

//! Abstract command interface to manipulate SessionItem in model context.

class CORE_EXPORT AbstractItemCommand
{
public:
    explicit AbstractItemCommand(SessionItem* receiver);
    virtual ~AbstractItemCommand() = default;

    virtual void execute() = 0;

    virtual void undo() = 0;

    void setObsolete(bool flag);
    bool isObsolete() const;

    std::string text() const;

    void setText(const std::string& text);

protected:
    bool m_is_obsolete;
    std::string m_text;
    SessionModel* m_model;
    Path m_item_path; //! Persistent path to the item which is receiver of given command.
};

} // namespace ModelView

#endif // MVVM_ABSTRACTITEMCOMMAND_H
