// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/insertnewitemcommand.h"
#include "mvvm/commands/abstractitemcommand.h"
#include "mvvm/model/function_types.h"
#include "mvvm/model/mvvm_types.h"
#include "mvvm/model/path.h"
#include "mvvm/model/sessionitem.h"
#include <QVariant>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

using namespace ModelView;

namespace {
std::string generate_description(const std::string& modelType, const TagRow& tagrow);
} // namespace

struct InsertNewItemCommand::InsertNewItemCommandImpl {
    item_factory_func_t m_factory_func;
    TagRow m_tagrow;
    Path m_item_path;
    std::string m_initial_identifier;
    InsertNewItemCommandImpl(item_factory_func_t func, TagRow tagrow)
        : m_factory_func(std::move(func)), m_tagrow(std::move(tagrow))
    {
    }
};

InsertNewItemCommand::InsertNewItemCommand(item_factory_func_t func, SessionItem* parent,
                                           const TagRow& tagrow)
    : AbstractItemCommand(parent), p_impl(std::make_unique<InsertNewItemCommandImpl>(func, tagrow))
{
    setResult(nullptr);
    p_impl->m_item_path = pathFromItem(parent);
}

InsertNewItemCommand::~InsertNewItemCommand() = default;

void InsertNewItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    auto item = parent->takeItem(p_impl->m_tagrow);
    // saving identifier for later redo
    if (p_impl->m_initial_identifier.empty())
        p_impl->m_initial_identifier = item->identifier();
    setResult(nullptr);
}

void InsertNewItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->m_item_path);
    auto child = p_impl->m_factory_func().release();
    // here we restore original identifier to get exactly same item on consequitive undo/redo
    if (!p_impl->m_initial_identifier.empty())
        child->setData(QVariant::fromValue(p_impl->m_initial_identifier), ItemDataRole::IDENTIFIER,
                       /*direct*/ true);

    setDescription(generate_description(child->modelType(), p_impl->m_tagrow));
    if (parent->insertItem(child, p_impl->m_tagrow)) {
        setResult(child);
    }
    else {
        delete child;
        setObsolete(true);
    }
}

namespace {
std::string generate_description(const std::string& modelType, const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "New item type '" << modelType << "' tag:'" << tagrow.m_tag << "', row:" << tagrow.m_row;
    return ostr.str();
}
} // namespace
