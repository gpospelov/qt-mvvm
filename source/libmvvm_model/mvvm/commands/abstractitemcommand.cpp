// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/commands/abstractitemcommand.h>
#include <mvvm/model/path.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <stdexcept>

using namespace ModelView;

struct AbstractItemCommand::AbstractItemCommandImpl {
    enum EStatus { INITIAL, AFTER_EXECUTE, AFTER_UNDO };
    bool is_obsolete{false};
    std::string text;
    EStatus status{INITIAL};
    SessionModel* model{nullptr};
    AbstractItemCommand* parent_impl{nullptr};
    CommandResult m_result;
    AbstractItemCommandImpl(AbstractItemCommand* parent) : parent_impl(parent) {}

    void set_after_execute() { status = AFTER_EXECUTE; }
    void set_after_undo() { status = AFTER_UNDO; }
    bool can_execute() const { return status != AFTER_EXECUTE; }
    bool can_undo() const { return status == AFTER_EXECUTE && !parent_impl->isObsolete(); }
};

AbstractItemCommand::AbstractItemCommand(SessionItem* receiver)
    : p_impl(std::make_unique<AbstractItemCommand::AbstractItemCommandImpl>(this))
{
    if (!receiver)
        throw std::runtime_error("Invalid item.");

    if (!receiver->model())
        throw std::runtime_error("Item doesn't have a model");

    p_impl->model = receiver->model();
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
    return p_impl->is_obsolete;
}

//! Returns command description.

std::string AbstractItemCommand::description() const
{
    return p_impl->text;
}

CommandResult AbstractItemCommand::result() const
{
    return p_impl->m_result;
}

//! Sets command obsolete flag.

void AbstractItemCommand::setObsolete(bool flag)
{
    p_impl->is_obsolete = flag;
}

//! Sets command description.

void AbstractItemCommand::setDescription(const std::string& text)
{
    p_impl->text = text;
}

Path AbstractItemCommand::pathFromItem(SessionItem* item) const
{
    return p_impl->model->pathFromItem(item);
}

SessionItem* AbstractItemCommand::itemFromPath(const Path& path) const
{
    return p_impl->model->itemFromPath(path);
}

SessionModel* AbstractItemCommand::model() const
{
    return p_impl->model;
}

void AbstractItemCommand::setResult(const CommandResult& command_result)
{
    p_impl->m_result = command_result;
}
