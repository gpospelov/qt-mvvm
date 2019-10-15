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
#include <sstream>

namespace
{
std::string generate_description(const std::string& modelType, const std::string& tag, int row);
} // namespace

using namespace ModelView;

struct CopyItemCommand::CopyItemCommandPrivate {
    std::string m_tag;
    int m_row;
    result_t m_result;
    std::unique_ptr<ItemBackupStrategy> m_backup_strategy;
    Path m_item_path;
    CopyItemCommandPrivate(std::string tag, int row)
        : m_tag(std::move(tag)), m_row(row), m_result(nullptr)
    {
    }
};

CopyItemCommand::CopyItemCommand(const SessionItem* item, SessionItem* parent,
                                           const std::string& tag, int row)
    : AbstractItemCommand(parent),
      p_impl(std::make_unique<CopyItemCommandPrivate>(tag, row))
{
    setDescription(generate_description(item->modelType(), p_impl->m_tag, p_impl->m_row));
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
    int row = p_impl->m_row < 0 ? parent->itemCount(p_impl->m_tag)-1 : p_impl->m_row;
    delete parent->takeItem({p_impl->m_tag, row});
    p_impl->m_result = nullptr;
}

void CopyItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    auto item = p_impl->m_backup_strategy->restoreItem();

    bool success = parent->insertItem(item.get(), {p_impl->m_tag, p_impl->m_row});
    p_impl->m_result = success ? item.release() : nullptr;
}

CopyItemCommand::result_t CopyItemCommand::result() const
{
    return p_impl->m_result;
}

namespace
{
std::string generate_description(const std::string& modelType, const std::string& tag, int row)
{
    std::ostringstream ostr;
    ostr << "Copy item'" << modelType << "' tag:'" << tag << "', row:" << row;
    return ostr.str();
}
} // namespace
