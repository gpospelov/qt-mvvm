// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "removeitemcommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "itembackupstrategy.h"
#include <sstream>

namespace
{
std::string generate_description(const std::string& tag, int row)
{
    std::ostringstream ostr;
    ostr << "Remove item from tag '" << tag << "', row " << row;
    return ostr.str();
}
} // namespace

using namespace ModelView;

class RemoveItemCommand::RemoveItemCommandPrivate
{
public:
    std::string m_tag;
    int m_row;
    result_t m_result;
    std::unique_ptr<ItemBackupStrategy> m_backup_strategy;
    Path m_item_path;
    RemoveItemCommandPrivate(std::string tag, int row) : m_tag(std::move(tag)), m_row(row), m_result(true){}
};

RemoveItemCommand::RemoveItemCommand(SessionItem* parent, std::string tag, int row)
    : AbstractItemCommand(parent), p_impl(std::make_unique<RemoveItemCommandPrivate>(tag, row))
{
    setDescription(generate_description(tag, row));
    p_impl->m_backup_strategy = parent->model()->backupStrategy();
    p_impl->m_item_path = pathFromItem(parent);
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    auto reco_item = p_impl->m_backup_strategy->restoreItem();
    parent->insertItem(reco_item.release(), p_impl->m_tag, p_impl->m_row);
}

void RemoveItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    auto child = parent->takeItem(p_impl->m_tag, p_impl->m_row);
    p_impl->m_backup_strategy->saveItem(child);
    delete child;
}

RemoveItemCommand::result_t RemoveItemCommand::result() const
{
    return p_impl->m_result;
}
