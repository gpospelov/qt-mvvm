// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "removeitemcommand.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "jsonitem.h"
#include "itemmanager.h"
#include <sstream>
#include <QJsonObject>

namespace  {
std::string description(const std::string& tag, int row) {
    std::ostringstream ostr;
    ostr << "Remove item from tag '" << tag << "', row " << row;
    return ostr.str();
}
}

using namespace ModelView;

RemoveItemCommand::RemoveItemCommand(SessionItem* parent, std::string tag, int row)
    : m_tag(std::move(tag))
    ,m_row(row)
    , m_model(parent->model())
    , m_result(true)
{
    m_parent_path = m_model->pathFromItem(parent);
    setText(description(tag, row));
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo()
{
    const auto& converter = m_model->manager()->item_converter();

    auto parent = m_model->itemFromPath(m_parent_path);

    auto reco_item = converter.from_json(*m_child_backup);
    parent->insertItem(reco_item.release(), m_tag, m_row);
}

void RemoveItemCommand::execute()
{
    const auto& converter = m_model->manager()->item_converter();

    auto parent = m_model->itemFromPath(m_parent_path);
    auto child = parent->takeItem(m_tag, m_row);

    m_child_backup = std::make_unique<QJsonObject>(converter.to_json(child));

    delete child;
}

RemoveItemCommand::result_t RemoveItemCommand::result() const
{
    return m_result;
}
