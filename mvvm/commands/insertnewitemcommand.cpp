// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "insertnewitemcommand.h"
#include "path.h"
#include "sessionitem.h"
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const std::string& modelType, const TagRow& tagrow);
} // namespace

struct InsertNewItemCommand::InsertNewItemCommandPrivate {
    item_factory_func_t factory_func;
    TagRow tagrow;
    result_t result;
    Path item_path;
    InsertNewItemCommandPrivate(item_factory_func_t func, TagRow tagrow)
        : factory_func(func), tagrow(std::move(tagrow)), result(nullptr)
    {
    }
};

InsertNewItemCommand::InsertNewItemCommand(item_factory_func_t func, SessionItem* parent,
                                           TagRow tagrow)
    : AbstractItemCommand(parent),
      p_impl(std::make_unique<InsertNewItemCommandPrivate>(func, tagrow))
{
    p_impl->item_path = pathFromItem(parent);
}

InsertNewItemCommand::~InsertNewItemCommand() = default;

void InsertNewItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    delete parent->takeItem(p_impl->tagrow);
    p_impl->result = nullptr;
}

void InsertNewItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto child = p_impl->factory_func().release();
    setDescription(generate_description(child->modelType(), p_impl->tagrow));
    parent->insertItem(child, p_impl->tagrow);
    p_impl->result = child;
}

InsertNewItemCommand::result_t InsertNewItemCommand::result() const
{
    return p_impl->result;
}

namespace
{
std::string generate_description(const std::string& modelType, const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "New item type '" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
