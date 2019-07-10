// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "insertitemcommand.h"
#include "path.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "itemfactory.h"
#include <sstream>

namespace
{
std::string generate_description(const std::string& modelType, const std::string& tag, int row);
} // namespace

using namespace ModelView;

struct InsertItemCommand::InsertItemCommandPrivate {
    model_type m_model_type;
    std::string m_tag;
    int m_row;
    result_t m_result;
    Path m_item_path;
    InsertItemCommandPrivate(model_type modelType, std::string tag, int row)
        : m_model_type(std::move(modelType)), m_tag(std::move(tag)), m_row(row), m_result(true)
    {
    }
};

InsertItemCommand::InsertItemCommand(model_type modelType, SessionItem* parent,
                                           std::string tag, int row)
    : AbstractItemCommand(parent),
      p_impl(std::make_unique<InsertItemCommandPrivate>(modelType, tag, row))
{
    setDescription(generate_description(p_impl->m_model_type, p_impl->m_tag, p_impl->m_row));
    p_impl->m_item_path = pathFromItem(parent);
}

InsertItemCommand::~InsertItemCommand() = default;

void InsertItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    int row = p_impl->m_row < 0 ? static_cast<int>(parent->getItems(p_impl->m_tag).size()) - 1
                                : p_impl->m_row;
    delete parent->takeItem(p_impl->m_tag, row);
}

void InsertItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    // FIXME get rid of manager in the favor of factory function generated in CommandService
    auto child = model()->factory()->createItem(p_impl->m_model_type).release();
    parent->insertItem(child, p_impl->m_tag, p_impl->m_row);
    p_impl->m_result = child;
}

InsertItemCommand::result_t InsertItemCommand::result() const
{
    return p_impl->m_result;
}

namespace
{
std::string generate_description(const std::string& modelType, const std::string& tag, int row)
{
    std::ostringstream ostr;
    ostr << "Insert item'" << modelType << "' tag:'" << tag << "', row:" << row;
    return ostr.str();
}
} // namespace
