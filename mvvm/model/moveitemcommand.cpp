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
    : AbstractItemCommand(new_parent), m_tag(tag), m_row(row), m_original_row(0), m_result(true)
{
    check_input_data(item, new_parent);
    m_target_parent_path = m_model->pathFromItem(new_parent);
    m_original_parent_path = m_model->pathFromItem(item->parent());
    auto tagRow = item->parent()->tagIndexOfItem(item);
    m_original_tag = tagRow.first;
    m_original_row = tagRow.second;
}

void MoveItemCommand::undo()
{
    auto current_parent = m_model->itemFromPath(m_target_parent_path);
    auto taken = current_parent->takeItem(m_tag, m_row);
    auto target_parent = m_model->itemFromPath(m_original_parent_path);
    target_parent->insertItem(taken, m_original_tag, m_original_row);
}

void MoveItemCommand::execute()
{
    auto original_parent = m_model->itemFromPath(m_original_parent_path);
    auto taken = original_parent->takeItem(m_original_tag, m_original_row);

    auto target_parent = m_model->itemFromPath(m_target_parent_path);
    target_parent->insertItem(taken, m_tag, m_row);
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
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Item doesn't have a parent");

}
} // namespace
