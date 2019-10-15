// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "removeitemcommand.h"
#include "itembackupstrategy.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const TagRow& tagrow);
} // namespace

struct RemoveItemCommand::RemoveItemCommandPrivate {
    TagRow m_tagrow;
    result_t m_result;
    std::unique_ptr<ItemBackupStrategy> m_backup_strategy;
    Path m_item_path;
    RemoveItemCommandPrivate(TagRow tagrow)
        : m_tagrow(std::move(tagrow)), m_result(true)
    {
    }
};

// ----------------------------------------------------------------------------

RemoveItemCommand::RemoveItemCommand(SessionItem* parent, TagRow tagrow)
    : AbstractItemCommand(parent), p_impl(std::make_unique<RemoveItemCommandPrivate>(tagrow))
{
    setDescription(generate_description(p_impl->m_tagrow));
    p_impl->m_backup_strategy = parent->model()->itemBackupStrategy();
    p_impl->m_item_path = pathFromItem(parent);
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    auto reco_item = p_impl->m_backup_strategy->restoreItem();
    parent->insertItem(reco_item.release(), p_impl->m_tagrow);
}

void RemoveItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    auto child = parent->takeItem(p_impl->m_tagrow);
    p_impl->m_backup_strategy->saveItem(child);
    delete child;
}

RemoveItemCommand::result_t RemoveItemCommand::result() const
{
    return p_impl->m_result;
}

namespace
{
std::string generate_description(const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Remove item from tag '" << tagrow.tag << "', row " << tagrow.row;
    return ostr.str();
}
} // namespace
