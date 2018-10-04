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

SessionItemData::DataRole::DataRole(const QVariant& data, int role) : m_data(data), m_role(role)
{
}

bool SessionItemData::DataRole::operator==(const SessionItemData::DataRole& other) const
{
    return m_role == other.m_role && Utils::IsTheSame(m_data, other.m_data);
}

QVector<int> SessionItemData::roles() const
{
    QVector<int> result;
    for (const auto& value : m_values)
        result.push_back(value.m_role);
    return result;
}

QVariant SessionItemData::data(int role) const
{
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;
    for (const auto& value : m_values) {
        if (value.m_role == role)
            return value.m_data;
    }
    return QVariant();
}

//! Sets the data for given role. Returns true if data was changed.

bool SessionItemData::setData(const QVariant& value, int role)
{
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;
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
