// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/removeitemcommand.h"
#include "mvvm/commands/commandutils.h"
#include "mvvm/interfaces/itembackupstrategy.h"
#include "mvvm/model/path.h"
#include "mvvm/model/sessionitem.h"
#include <sstream>

using namespace ModelView;

namespace {
std::string generate_description(const TagRow& tagrow);
} // namespace

struct RemoveItemCommand::RemoveItemCommandImpl {
    TagRow tagrow;
    std::unique_ptr<ItemBackupStrategy> backup_strategy;
    Path item_path;
    RemoveItemCommandImpl(TagRow tagrow) : tagrow(std::move(tagrow)) {}
};

RemoveItemCommand::RemoveItemCommand(SessionItem* parent, TagRow tagrow)
    : AbstractItemCommand(parent)
    , p_impl(std::make_unique<RemoveItemCommandImpl>(std::move(tagrow)))
{
    setResult(false);

    setDescription(generate_description(p_impl->tagrow));
    p_impl->backup_strategy = CreateItemBackupStrategy(parent->model());
    p_impl->item_path = pathFromItem(parent);
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    parent->insertItem(p_impl->backup_strategy->restoreItem(), p_impl->tagrow);
}

void RemoveItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    if (auto child = parent->takeItem(p_impl->tagrow); child) {
        p_impl->backup_strategy->saveItem(child.get());
        setResult(true);
    } else {
        setResult(false);
        setObsolete(true);
    }
}

namespace {
std::string generate_description(const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Remove item from tag '" << tagrow.tag << "', row " << tagrow.row;
    return ostr.str();
}
} // namespace
