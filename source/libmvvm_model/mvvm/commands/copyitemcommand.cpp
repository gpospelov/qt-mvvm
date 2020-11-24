// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/commands/copyitemcommand.h>
#include <mvvm/interfaces/itembackupstrategy.h>
#include <mvvm/interfaces/itemcopystrategy.h>
#include <mvvm/model/path.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const std::string& modelType, const TagRow& tagrow);
} // namespace

struct CopyItemCommand::CopyItemCommandImpl {
    TagRow tagrow;
    result_t result;
    std::unique_ptr<ItemBackupStrategy> backup_strategy;
    Path item_path;
    CopyItemCommandImpl(TagRow tagrow) : tagrow(std::move(tagrow)), result(nullptr) {}
};

CopyItemCommand::CopyItemCommand(const SessionItem* item, SessionItem* parent, TagRow tagrow)
    : AbstractItemCommand(parent), p_impl(std::make_unique<CopyItemCommandImpl>(std::move(tagrow)))
{
    setCommandResult(nullptr);

    setDescription(generate_description(item->modelType(), p_impl->tagrow));
    p_impl->backup_strategy = parent->model()->itemBackupStrategy();
    p_impl->item_path = pathFromItem(parent);

    auto copy_strategy = parent->model()->itemCopyStrategy(); // to modify id's
    auto item_copy = copy_strategy->createCopy(item);

    p_impl->backup_strategy->saveItem(item_copy.get());
}

CopyItemCommand::~CopyItemCommand() = default;

void CopyItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    delete parent->takeItem(p_impl->tagrow);
    setCommandResult(nullptr);
    p_impl->result = nullptr;
}

void CopyItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto item = p_impl->backup_strategy->restoreItem();
    if (parent->insertItem(item.get(), p_impl->tagrow)) {
        p_impl->result = item.release();
        setCommandResult(item.release());
    } else {
        setCommandResult(nullptr);
        p_impl->result = nullptr;
        setObsolete(true);
    }
}

CopyItemCommand::result_t CopyItemCommand::result() const
{
    return p_impl->result;
}

namespace
{
std::string generate_description(const std::string& modelType, const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Copy item'" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
