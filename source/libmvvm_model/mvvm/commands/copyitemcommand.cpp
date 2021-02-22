// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/copyitemcommand.h"
#include "mvvm/commands/commandutils.h"
#include "mvvm/interfaces/itembackupstrategy.h"
#include "mvvm/interfaces/itemcopystrategy.h"
#include "mvvm/model/path.h"
#include "mvvm/model/sessionitem.h"
#include <sstream>

using namespace ModelView;

namespace {
std::string generate_description(const std::string& modelType, const TagRow& tagrow);
} // namespace

struct CopyItemCommand::CopyItemCommandImpl {
    TagRow tagrow;
    std::unique_ptr<ItemBackupStrategy> backup_strategy;
    Path item_path;
    CopyItemCommandImpl(TagRow tagrow) : tagrow(std::move(tagrow)) {}
};

CopyItemCommand::CopyItemCommand(const SessionItem* item, SessionItem* parent, TagRow tagrow)
    : AbstractItemCommand(parent), p_impl(std::make_unique<CopyItemCommandImpl>(std::move(tagrow)))
{
    setResult(nullptr);

    setDescription(generate_description(item->modelType(), p_impl->tagrow));
    p_impl->backup_strategy = CreateItemBackupStrategy(parent->model());
    p_impl->item_path = pathFromItem(parent);

    auto copy_strategy = CreateItemCopyStrategy(parent->model()); // to modify id's
    auto item_copy = copy_strategy->createCopy(item);

    p_impl->backup_strategy->saveItem(item_copy.get());
}

CopyItemCommand::~CopyItemCommand() = default;

void CopyItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    parent->takeItem(p_impl->tagrow);
    setResult(nullptr);
}

void CopyItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto item = parent->insertItem(p_impl->backup_strategy->restoreItem(), p_impl->tagrow);
    // FIXME revise behaviour in the case of invalid operation. Catch or not here?
    setResult(item);
    setObsolete(!item); // command is osbolete if insertion failed
}

namespace {
std::string generate_description(const std::string& modelType, const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Copy item'" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
