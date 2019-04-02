// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "datarole.h"
#include "customvariants.h"

using namespace ModelView;

DataRole::DataRole(QVariant data, int role)
    : m_data(std::move(data)), m_role(role)
{
}

bool DataRole::operator==(const DataRole& other) const
{
    return m_role == other.m_role && Utils::IsTheSame(m_data, other.m_data);
}

