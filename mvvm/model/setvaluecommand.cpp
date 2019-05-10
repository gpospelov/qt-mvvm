// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "setvaluecommand.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include <sstream>

namespace  {
std::string description(const std::string& str) {
    std::ostringstream ostr;
    ostr << "Set value " << str;
    return ostr.str();
}
}


using namespace ModelView;

SetValueCommand::SetValueCommand(SessionItem* item, QVariant value, int role)
    : m_value(std::move(value))
    , m_role(role)
    , m_model(item->model())
    , m_result(false)
{
    Q_ASSERT(m_model);
    m_path = m_model->pathFromItem(item);
    setText(description(m_value.toString().toStdString()));
}

void SetValueCommand::undo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data(m_role);
    m_result = item->setDataIntern(m_value, m_role);
    setObsolete(!m_result);
    m_value = old;
}

void SetValueCommand::execute()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data(m_role);
    m_result = item->setDataIntern(m_value, m_role);
    setObsolete(!m_result);
    m_value = old;
}

//! Returns result of the command, which is bool value denoting that the value was set succesfully.
//! The value 'false' means that the data is the same and no change was required.

SetValueCommand::result_t SetValueCommand::result() const
{
    return m_result;
}

