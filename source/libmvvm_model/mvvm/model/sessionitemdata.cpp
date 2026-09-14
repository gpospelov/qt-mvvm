// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/sessionitemdata.h"
#include "mvvm/model/customvariants.h"
#include <algorithm>
#include <QString>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace ModelView;

std::vector<int> SessionItemData::roles() const
{
    std::vector<int> result;
    for (const auto& value : m_values)
        result.push_back(value.m_role);
    return result;
}

Variant SessionItemData::data(int role) const
{
    for (const auto& value : m_values) {
        if (value.m_role == role)
            return value.m_data;
    }
    return Variant();
}

//! Sets the data for given role. Returns true if data was changed.
//! If variant is invalid, corresponding role will be removed.

bool SessionItemData::setData(const Variant& newValue, int role)
{
    if (newValue.userType() == QMetaType::fromType<QString>().id()) {
        throw std::runtime_error("SessionItemData::setData() -> Attempt to set a QString based variant");
    }

    for (auto it = m_values.begin(); it != m_values.end(); ++it) {

        if (it->m_role == role) {

            // Found a previous value for the role.

            if (!newValue.isValid()) {
                // Delete the existing value/role:
                m_values.erase(it);
                return true;
            }

            if (newValue.userType() != it->m_data.userType()) {
                // Error: A value should only get replaced by one of the same type!
                std::ostringstream ostr;
                ostr << "SessionItemData::setData() -> Error: Variant types mismatch. "
                     << "Old variant type '" << it->m_data.typeName() << "' "
                     << "New variant type '" << newValue.typeName() << "\n";
                throw std::runtime_error(ostr.str());
            }

            if (it->m_data == newValue) {
                // Same value (no change).
                return false;
            }

            // Replace the value.
            it->m_data = newValue;
            return true;
        }
    }

    // Insert new value/role:
    m_values.push_back(DataRole(newValue, role));

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

//! Returns true if item has data with given role.

bool SessionItemData::hasData(int role) const
{
    auto has_role = [role](const auto& x) { return x.m_role == role; };
    return std::find_if(m_values.begin(), m_values.end(), has_role) != m_values.end();
}
