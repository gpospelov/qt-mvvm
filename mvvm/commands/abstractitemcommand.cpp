// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "abstractitemcommand.h"
#include "path.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <stdexcept>

using namespace ModelView;

struct AbstractItemCommand::AbstractItemCommandImpl {
    enum EStatus { INITIAL, AFTER_EXECUTE, AFTER_UNDO };

    AbstractItemCommandImpl() : m_is_obsolete(false), m_status(INITIAL), m_model(nullptr) {}

    bool can_execute() const { return m_status != AFTER_EXECUTE; }
    bool can_undo() const { return m_status == AFTER_EXECUTE; }
    void set_after_execute() { m_status = AFTER_EXECUTE; }
    void set_after_undo() { m_status = AFTER_UNDO; }

    bool m_is_obsolete;
    std::string m_text;
    EStatus m_status;
    SessionModel* m_model;
};

AbstractItemCommand::AbstractItemCommand(SessionItem* receiver)
    : p_impl(std::make_unique<AbstractItemCommand::AbstractItemCommandImpl>())
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
    if (!p_impl->can_execute())
        throw std::runtime_error("Can't execute the command. Wrong order.");

    execute_command();

    p_impl->set_after_execute();
}

//! Undo command as it was before execution.

void AbstractItemCommand::undo()
{
    if (!p_impl->can_undo())
        throw std::runtime_error("Can't undo the command. Wrong order.");

    undo_command();

    p_impl->set_after_undo();
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
    return p_impl->m_model->itemFromPath(std::move(path));
}

SessionModel* AbstractItemCommand::model() const
{
    return p_impl->m_model;
}
