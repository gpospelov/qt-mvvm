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

CommandAdapter::CommandAdapter(std::shared_ptr<AbstractItemCommand> command)
    : m_command(std::move(command))
{

}

CommandAdapter::~CommandAdapter() = default;

void CommandAdapter::undo()
{
    m_command->undo();
}

void CommandAdapter::redo()
{
    m_command->execute();
    setObsolete(m_command->isObsolete());
    setText(m_command->text());
}
