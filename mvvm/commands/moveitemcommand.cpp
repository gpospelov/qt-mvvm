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
#include <sstream>
#include <stdexcept>

using namespace ModelView;

namespace
{
void check_input_data(const SessionItem* item, const SessionItem* parent);
std::string generate_description(const std::string& tag, int row);
} // namespace

struct MoveItemCommand::MoveItemCommandPrivate {
    std::string m_target_tag;
    int m_target_row;
    Path m_target_parent_path;
    Path m_original_parent_path;
    std::string m_original_tag;
    int m_original_row;
    result_t m_result;
    MoveItemCommandPrivate(std::string tag, int row)
        : m_target_tag(std::move(tag)), m_target_row(row), m_original_row(0), m_result(true)
    {
    }
};

MoveItemCommand::MoveItemCommand(SessionItem* item, SessionItem* new_parent, std::string tag,
                                 int row)
    : AbstractItemCommand(new_parent), p_impl(std::make_unique<MoveItemCommandPrivate>(tag, row))
{
    check_input_data(item, new_parent);
    setDescription(generate_description(p_impl->m_target_tag, p_impl->m_target_row));

    p_impl->m_target_parent_path = pathFromItem(new_parent);
    p_impl->m_original_parent_path = pathFromItem(item->parent());
    auto [original_tag, original_row] = item->parent()->tagRowOfItem(item);
    p_impl->m_original_tag = original_tag;
    p_impl->m_original_row = original_row;

    if (item->parent()->isSinglePropertyTag(p_impl->m_original_tag))
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Single property tag.");

    if (new_parent->isSinglePropertyTag(p_impl->m_target_tag))
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Single property tag.");

    if (item->parent() == new_parent) {
        if (p_impl->m_target_row >= new_parent->itemCount(p_impl->m_target_tag))
            throw std::runtime_error(
                "MoveCommand::MoveCommand() -> move index exceeds number of items in a tag");
    }
}

MoveItemCommand::~MoveItemCommand() = default;

void MoveItemCommand::undo_command()
{
    // first find items
    auto current_parent = itemFromPath(p_impl->m_target_parent_path);
    auto target_parent = itemFromPath(p_impl->m_original_parent_path);

    // then make manipulations
    int row = p_impl->m_target_row < 0 ? current_parent->itemCount(p_impl->m_target_tag) - 1
                                       : p_impl->m_target_row;
    auto taken = current_parent->takeItem({p_impl->m_target_tag, row});
    target_parent->insertItem(taken, {p_impl->m_original_tag, p_impl->m_original_row});

    // adjusting new addresses
    p_impl->m_target_parent_path = pathFromItem(current_parent);
    p_impl->m_original_parent_path = pathFromItem(target_parent);
}

void MoveItemCommand::execute_command()
{
    // first find items
    auto original_parent = itemFromPath(p_impl->m_original_parent_path);
    auto target_parent = itemFromPath(p_impl->m_target_parent_path);

    // then make manipulations
    auto taken = original_parent->takeItem({p_impl->m_original_tag, p_impl->m_original_row});

    // FIXME If something went wrong will throw an exception. Shell we try to proceed instead
    // and try to gently resolve situations maximum/minimum/reached?

    if (!taken)
        throw std::runtime_error("MoveItemCommand::execute() -> Can't take an item.");

    bool succeeded = target_parent->insertItem(taken, {p_impl->m_target_tag, p_impl->m_target_row});
    if (!succeeded)
        throw std::runtime_error("MoveItemCommand::execute() -> Can't insert item.");

    // adjusting new addresses
    p_impl->m_target_parent_path = pathFromItem(target_parent);
    p_impl->m_original_parent_path = pathFromItem(original_parent);
}

MoveItemCommand::result_t MoveItemCommand::result() const
{
    return p_impl->m_result;
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

std::string generate_description(const std::string& tag, int row)
{
    std::ostringstream ostr;
    ostr << "Move item to tag '" << tag << "', row:" << row;
    return ostr.str();
}
} // namespace
