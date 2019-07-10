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

class AbstractItemCommand::AbstractItemCommandPrivate {
public:
    AbstractItemCommandPrivate() : m_is_obsolete(false), m_model(nullptr){}
    bool m_is_obsolete;
    std::string m_text;
    SessionModel* m_model;
};

AbstractItemCommand::AbstractItemCommand(SessionItem* receiver)
    : p_impl(std::make_unique<AbstractItemCommand::AbstractItemCommandPrivate>())
{
    if (!receiver)
        throw std::runtime_error("Invalid item.");

    if (!receiver->model())
        throw std::runtime_error("Item doesn't have a model");

    p_impl->m_model = receiver->model();
}

AbstractItemCommand::~AbstractItemCommand() = default;

//! Execute command.

void AbstractItemCommand::execute()
{
    execute_command();
}

//! Undo command as it was before execution.

void AbstractItemCommand::undo()
{
    undo_command();
}

//! Returns whether the command is obsolete (which means that it shouldn't be kept in the stack).

bool AbstractItemCommand::isObsolete() const
{
    return p_impl->m_is_obsolete;
}

//! Returns command description.

std::string AbstractItemCommand::description() const
{
    return p_impl->m_text;
}

//! Sets command obsolete flag.

void AbstractItemCommand::setObsolete(bool flag)
{
    p_impl->m_is_obsolete = flag;
}

//! Sets command description.

void AbstractItemCommand::setDescription(const std::string& text)
{
    p_impl->m_text = text;
}

Path AbstractItemCommand::pathFromItem(SessionItem* item) const
{
    return p_impl->m_model->pathFromItem(item);
}

SessionItem* AbstractItemCommand::itemFromPath(Path path) const
{
    return p_impl->m_model->itemFromPath(path);
}

SessionModel* AbstractItemCommand::model() const
{
    return p_impl->m_model;
}

