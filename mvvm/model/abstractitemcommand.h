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
#include <QString>

namespace ModelView
{

//! Abstract command interface to manipulate SessionItem in model context.

class CORE_EXPORT AbstractItemCommand
{
public:
    AbstractItemCommand();
    virtual ~AbstractItemCommand() = default;

    virtual void execute() = 0;

    virtual void undo() = 0;

    void setObsolete(bool flag);
    bool isObsolete() const;

    QString text() const;

    void setText(const QString& text);

private:
    bool m_is_obsolete;
    QString m_text;
};

} // namespace ModelView

#endif // MVVM_ABSTRACTITEMCOMMAND_H
