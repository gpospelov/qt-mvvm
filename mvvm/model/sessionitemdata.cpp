// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitemdata.h"
#include "itemutils.h"

using namespace ModelView;

std::vector<int> SessionItemData::roles() const
{
    std::vector<int> result;
    for (const auto& value : m_values)
        result.push_back(value.m_role);
    return result;
}

QVariant SessionItemData::data(int role) const
{
    for (const auto& value : m_values) {
        if (value.m_role == role)
            return value.m_data;
    }
    return QVariant();
}

//! Sets the data for given role. Returns true if data was changed.

bool SessionItemData::setData(const QVariant& value, int role)
{
    for (auto it = m_values.begin(); it != m_values.end(); ++it) {
        if (it->m_role == role) {
            if (value.isValid()) {
                if (Utils::IsTheSame(it->m_data, value))
                    return false;
                it->m_data = value;
            } else {
                m_values.erase(it);
            }
            return true;
        }
    }
    m_values.push_back(DataRole(value, role));
    return true;
}

SessionItemData::const_iterator SessionItemData::begin() const
{
    return m_values.begin();
}

SessionItemData::const_iterator SessionItemData::end() const
{
    return m_values.end();
}
