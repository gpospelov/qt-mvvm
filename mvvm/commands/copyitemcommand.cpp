// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "copyitemcommand.h"
#include "path.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "itemcopystrategy.h"
#include "itembackupstrategy.h"
#include "tagrow.h"
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const std::string& modelType, const TagRow& tagrow);
} // namespace

struct CopyItemCommand::CopyItemCommandPrivate {
    TagRow m_tagrow;
    result_t m_result;
    std::unique_ptr<ItemBackupStrategy> m_backup_strategy;
    Path m_item_path;
    CopyItemCommandPrivate(TagRow tagrow)
        : m_tagrow(std::move(tagrow)), m_result(nullptr)
    {
    }
};

CopyItemCommand::CopyItemCommand(const SessionItem* item, SessionItem* parent,
                                           TagRow tagrow)
    : AbstractItemCommand(parent),
      p_impl(std::make_unique<CopyItemCommandPrivate>(tagrow))
{
    setDescription(generate_description(item->modelType(), p_impl->m_tagrow));
    p_impl->m_backup_strategy = parent->model()->itemBackupStrategy();
    p_impl->m_item_path = pathFromItem(parent);

    auto copy_strategy = parent->model()->itemCopyStrategy(); // to modify id's
    auto item_copy = copy_strategy->createCopy(item);

    p_impl->m_backup_strategy->saveItem(item_copy.get());
}

CopyItemCommand::~CopyItemCommand() = default;

void CopyItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    delete parent->takeItem(p_impl->m_tagrow);
    p_impl->m_result = nullptr;
}

void CopyItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    auto item = p_impl->m_backup_strategy->restoreItem();
    bool success = parent->insertItem(item.get(), p_impl->m_tagrow);
    p_impl->m_result = success ? item.release() : nullptr;
}

CopyItemCommand::result_t CopyItemCommand::result() const
{
    return p_impl->m_result;
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
