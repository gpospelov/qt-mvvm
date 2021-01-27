// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/abstractitemcommand.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/model/path.h"
#include "mvvm/model/sessionitem.h"
#include <stdexcept>

using namespace ModelView;

struct AbstractItemCommand::AbstractItemCommandImpl {
    enum class Status { initial, after_execute, after_undo };
    bool m_isObsolete{false};
    std::string m_text;
    Status m_status{Status::initial};
    SessionModel* m_model{nullptr};
    AbstractItemCommand* m_self{nullptr};
    CommandResult m_result;
    AbstractItemCommandImpl(AbstractItemCommand* parent) : m_self(parent) {}

    void set_after_execute() { m_status = Status::after_execute; }
    void set_after_undo() { m_status = Status::after_undo; }
    bool can_execute() const { return m_status != Status::after_execute; }
    bool can_undo() const { return m_status == Status::after_execute && !m_self->isObsolete(); }
};

AbstractItemCommand::AbstractItemCommand(SessionItem* receiver)
    : p_impl(std::make_unique<AbstractItemCommand::AbstractItemCommandImpl>(this))
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
    return p_impl->m_isObsolete;
}

//! Returns command description.

std::string AbstractItemCommand::description() const
{
    return p_impl->m_text;
}

CommandResult AbstractItemCommand::result() const
{
    return p_impl->m_result;
}

//! Sets command obsolete flag.

void AbstractItemCommand::setObsolete(bool flag)
{
    p_impl->m_isObsolete = flag;
}

//! Sets command description.

void AbstractItemCommand::setDescription(const std::string& text)
{
    p_impl->m_text = text;
}

Path AbstractItemCommand::pathFromItem(SessionItem* item) const
{
    return Utils::PathFromItem(item);
}

SessionItem* AbstractItemCommand::itemFromPath(const Path& path) const
{
    return Utils::ItemFromPath(*p_impl->m_model, path);
}

SessionModel* AbstractItemCommand::model() const
{
    return p_impl->m_model;
}

void AbstractItemCommand::setResult(const CommandResult& command_result)
{
    p_impl->m_result = command_result;
}
