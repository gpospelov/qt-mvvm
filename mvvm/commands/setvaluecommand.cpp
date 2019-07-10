// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "setvaluecommand.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <QVariant>
#include <sstream>

namespace
{
std::string generate_description(const std::string& str)
{
    std::ostringstream ostr;
    ostr << "Set value " << str;
    return ostr.str();
}
} // namespace

using namespace ModelView;

struct SetValueCommand::SetValueCommandPrivate {
    QVariant m_value; //! Value to set as a result of command execution.
    int m_role;
    result_t m_result;
    Path m_item_path;
    SetValueCommandPrivate(QVariant value, int role)
        : m_value(std::move(value)), m_role(role), m_result(false)
    {
    }
};

SetValueCommand::SetValueCommand(SessionItem* item, QVariant value, int role)
    : AbstractItemCommand(item), p_impl(std::make_unique<SetValueCommandPrivate>(value, role))
{
    setDescription(generate_description(p_impl->m_value.toString().toStdString()));
    p_impl->m_item_path = pathFromItem(item);
}

SetValueCommand::~SetValueCommand() = default;

void SetValueCommand::undo_command()
{
    swap_values();
}

void SetValueCommand::execute_command()
{
    swap_values();
}

void SetValueCommand::swap_values()
{
    auto item = itemFromPath(p_impl->m_item_path);
    QVariant old = item->data(p_impl->m_role);
    p_impl->m_result = item->setDataIntern(p_impl->m_value, p_impl->m_role);
    setObsolete(!p_impl->m_result);
    p_impl->m_value = old;
}

//! Returns result of the command, which is bool value denoting that the value was set succesfully.
//! The value 'false' means that the data is the same and no change was required.

SetValueCommand::result_t SetValueCommand::result() const
{
    return p_impl->m_result;
}
