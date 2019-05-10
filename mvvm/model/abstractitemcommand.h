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
#include <QUndoCommand>

namespace ModelView
{

//! Command for unddo/redo to insert new item.

class CORE_EXPORT AbstractItemCommand : public QUndoCommand
{
public:
};

} // namespace ModelView

#endif // MVVM_ABSTRACTITEMCOMMAND_H
