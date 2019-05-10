// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "insertnewitemcommand.h"
#include "itemmanager.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <sstream>

namespace  {
std::string description(const std::string& modelType, const std::string& tag, int row) {
    std::ostringstream ostr;
    ostr << "New item type '" << modelType << "' tag:'" << tag << "', row:" << row;
    return ostr.str();
}
}

using namespace ModelView;

InsertNewItemCommand::InsertNewItemCommand(model_type modelType, SessionItem* parent,
                                           std::string tag, int row)
    :  AbstractItemCommand(parent), m_tag(std::move(tag)), m_row(row), m_model_type(std::move(modelType))
{
    setText(description(m_model_type, tag, row));
}

void InsertNewItemCommand::undo()
{
    auto parent = m_model->itemFromPath(m_item_path);
    int row = m_row < 0 ? static_cast<int>(parent->getItems(m_tag).size()) - 1 : m_row;
    delete parent->takeItem(m_tag, row);
    m_result = nullptr;
}

void InsertNewItemCommand::execute()
{
    auto parent = m_model->itemFromPath(m_item_path);
    auto child = m_model->manager()->createItem(m_model_type).release();
    parent->insertItem(child, m_tag, m_row);
    m_result = child;
}

InsertNewItemCommand::result_t InsertNewItemCommand::result() const
{
    return m_result;
}
