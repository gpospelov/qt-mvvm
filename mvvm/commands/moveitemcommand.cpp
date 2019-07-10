// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "moveitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <stdexcept>

using namespace ModelView;

namespace
{
void check_input_data(const SessionItem* item, const SessionItem* parent);
}

MoveItemCommand::MoveItemCommand(SessionItem* item, SessionItem* new_parent, const std::string& tag,
                                 int row)
    : AbstractItemCommand(new_parent), m_target_tag(tag), m_target_row(row), m_original_row(0), m_result(true)
{
    check_input_data(item, new_parent);
    m_target_parent_path = m_model->pathFromItem(new_parent);
    m_original_parent_path = m_model->pathFromItem(item->parent());
    auto tagRow = item->parent()->tagIndexOfItem(item);
    m_original_tag = tagRow.first;
    m_original_row = tagRow.second;

    if (item->parent()->isSinglePropertyTag(m_original_tag))
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Single property tag.");

    if (new_parent->isSinglePropertyTag(m_target_tag))
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Single property tag.");
}

void MoveItemCommand::undo_command()
{
    // first find items
    auto current_parent = m_model->itemFromPath(m_target_parent_path);
    auto target_parent = m_model->itemFromPath(m_original_parent_path);

    // then make manipulations
    int row = m_target_row < 0 ? static_cast<int>(current_parent->getItems(m_target_tag).size()) - 1 : m_target_row;
    auto taken = current_parent->takeItem(m_target_tag, row);
    target_parent->insertItem(taken, m_original_tag, m_original_row);

    // adjusting new addresses
    m_target_parent_path = m_model->pathFromItem(current_parent);
    m_original_parent_path = m_model->pathFromItem(target_parent);
}

void MoveItemCommand::execute_command()
{
    // first find items
    auto original_parent = m_model->itemFromPath(m_original_parent_path);
    auto target_parent = m_model->itemFromPath(m_target_parent_path);

    // then make manipulations
    auto taken = original_parent->takeItem(m_original_tag, m_original_row);

    // FIXME If something went wrong will throw an exception. Shell we try to proceed instead
    // and try to gently resolve situations maximum/minimum/reached?

    if (!taken)
        throw std::runtime_error("MoveItemCommand::execute() -> Can't take an item.");

    bool succeeded = target_parent->insertItem(taken, m_target_tag, m_target_row);
    if (!succeeded)
        throw std::runtime_error("MoveItemCommand::execute() -> Can't insert item.");

    // adjusting new addresses
    m_target_parent_path = m_model->pathFromItem(target_parent);
    m_original_parent_path = m_model->pathFromItem(original_parent);
}

MoveItemCommand::result_t MoveItemCommand::result() const
{
    return m_result;
}

namespace
{
void check_input_data(const SessionItem* item, const SessionItem* parent)
{
    if (!item || !item->model())
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Invalid input item");

    if (!parent || !parent->model())
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Invalid parent item");

    if (item->model() != parent->model())
        throw std::runtime_error(
            "MoveItemCommand::MoveItemCommand() -> Items belong to different models");

    if (!item->parent())
        throw std::runtime_error(
            "MoveItemCommand::MoveItemCommand() -> Item doesn't have a parent");
}
} // namespace
