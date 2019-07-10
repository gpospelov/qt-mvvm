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

RemoveItemCommand::RemoveItemCommand(SessionItem* parent, std::string tag, int row)
    : AbstractItemCommand(parent), m_tag(std::move(tag)), m_row(row), m_result(true)
{
    setDescription(generate_description(tag, row));
    m_backup_strategy = parent->model()->backupStrategy();
    m_item_path = pathFromItem(parent);
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo_command()
{
    auto parent = itemFromPath(m_item_path);
    auto reco_item = m_backup_strategy->restoreItem();
    parent->insertItem(reco_item.release(), m_tag, m_row);
}

void RemoveItemCommand::execute_command()
{
    auto parent = itemFromPath(m_item_path);
    auto child = parent->takeItem(m_tag, m_row);
    m_backup_strategy->saveItem(child);
    delete child;
}

RemoveItemCommand::result_t RemoveItemCommand::result() const
{
    return m_result;
}
