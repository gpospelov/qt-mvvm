// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "commandadapter.h"
#include "abstractitemcommand.h"

using namespace ModelView;

void CommandAdapter::undo()
{
    m_command->undo();
}

void CommandAdapter::redo()
{
    m_command->redo();
}
