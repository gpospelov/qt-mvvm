// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "abstractitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <stdexcept>

using namespace ModelView;

AbstractItemCommand::AbstractItemCommand(SessionItem* receiver)
    : m_is_obsolete(false), m_model(nullptr)
{
    if (!receiver)
        throw std::runtime_error("Invalid item.");

    if (!receiver->model())
        throw std::runtime_error("Item doesn't have a model");

    m_model = receiver->model();
    m_item_path = m_model->pathFromItem(receiver);
}

//! Sets command obsolete flag.

void AbstractItemCommand::setObsolete(bool flag)
{
    m_is_obsolete = flag;
}

//! Returns whether the command is obsolete (which means that it shouldn't be kept in the stack).

bool AbstractItemCommand::isObsolete() const
{
    return m_is_obsolete;
}

//! Returns command description.

std::string AbstractItemCommand::description() const
{
    return m_text;
}

//! Sets command description.

void AbstractItemCommand::setDescription(const std::string& text)
{
    m_text = text;
}

//! Finds the item which is the receiver of given command.

SessionItem* AbstractItemCommand::findReceiver() const
{
    return m_model->itemFromPath(m_item_path);
}
