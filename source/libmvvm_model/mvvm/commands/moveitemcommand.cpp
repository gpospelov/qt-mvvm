// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/moveitemcommand.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/path.h"
#include "mvvm/model/sessionitem.h"
#include <sstream>
#include <stdexcept>

using namespace ModelView;

namespace {
void check_input_data(const SessionItem* item, const SessionItem* parent);
std::string generate_description(const TagRow& tagrow);
} // namespace

struct MoveItemCommand::MoveItemCommandImpl {
    TagRow target_tagrow;
    Path target_parent_path;
    Path original_parent_path;
    TagRow original_tagrow;
    MoveItemCommandImpl(TagRow tagrow) : target_tagrow(std::move(tagrow))
    {
        if (target_tagrow.row < 0)
            throw std::runtime_error("MoveItemCommand() -> Error. Uninitialized target row");
    }
};

MoveItemCommand::MoveItemCommand(SessionItem* item, SessionItem* new_parent, TagRow tagrow)
    : AbstractItemCommand(new_parent), p_impl(std::make_unique<MoveItemCommandImpl>(tagrow))
{
    setResult(true);

    check_input_data(item, new_parent);
    setDescription(generate_description(p_impl->target_tagrow));

    p_impl->target_parent_path = pathFromItem(new_parent);
    p_impl->original_parent_path = pathFromItem(item->parent());
    p_impl->original_tagrow = item->tagRow();

    if (Utils::IsSinglePropertyTag(*item->parent(), p_impl->original_tagrow.tag))
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Single property tag.");

    if (Utils::IsSinglePropertyTag(*new_parent, p_impl->target_tagrow.tag))
        throw std::runtime_error("MoveItemCommand::MoveItemCommand() -> Single property tag.");

    if (item->parent() == new_parent) {
        if (p_impl->target_tagrow.row >= new_parent->itemCount(p_impl->target_tagrow.tag))
            throw std::runtime_error(
                "MoveCommand::MoveCommand() -> move index exceeds number of items in a tag");
    }
}

MoveItemCommand::~MoveItemCommand() = default;

void MoveItemCommand::undo_command()
{
    // first find items
    auto current_parent = itemFromPath(p_impl->target_parent_path);
    auto target_parent = itemFromPath(p_impl->original_parent_path);

    // then make manipulations
    auto taken = current_parent->takeItem(p_impl->target_tagrow);
    target_parent->insertItem(std::move(taken), p_impl->original_tagrow);

    // adjusting new addresses
    p_impl->target_parent_path = pathFromItem(current_parent);
    p_impl->original_parent_path = pathFromItem(target_parent);
}

void MoveItemCommand::execute_command()
{
    // first find items
    auto original_parent = itemFromPath(p_impl->original_parent_path);
    auto target_parent = itemFromPath(p_impl->target_parent_path);

    // then make manipulations
    auto taken = original_parent->takeItem(p_impl->original_tagrow);

    if (!taken)
        throw std::runtime_error("MoveItemCommand::execute() -> Can't take an item.");

    if (!target_parent->insertItem(std::move(taken), p_impl->target_tagrow))
        throw std::runtime_error("MoveItemCommand::execute() -> Can't insert item.");

    // adjusting new addresses
    p_impl->target_parent_path = pathFromItem(target_parent);
    p_impl->original_parent_path = pathFromItem(original_parent);
}

namespace {
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

std::string generate_description(const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Move item to tag '" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
