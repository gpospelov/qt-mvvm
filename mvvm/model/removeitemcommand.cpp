// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "removeitemcommand.h"
#include "itemmanager.h"
#include "jsonitem.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <QJsonObject>
#include <sstream>

namespace
{
std::string description(const std::string& tag, int row)
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
    setDescription(description(tag, row));
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo()
{
    const auto& converter = m_model->manager()->item_converter();

    auto parent = findReceiver();

    auto reco_item = converter.from_json(*m_child_backup);
    parent->insertItem(reco_item.release(), m_tag, m_row);
}

void RemoveItemCommand::execute()
{
    const auto& converter = m_model->manager()->item_converter();

    auto parent = findReceiver();
    auto child = parent->takeItem(m_tag, m_row);

    m_child_backup = std::make_unique<QJsonObject>(converter.to_json(child));

    delete child;
}

RemoveItemCommand::result_t RemoveItemCommand::result() const
{
    return m_result;
}
