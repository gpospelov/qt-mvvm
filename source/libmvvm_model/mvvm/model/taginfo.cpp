// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/taginfo.h"
#include "mvvm/utils/containerutils.h"
#include <sstream>
#include <stdexcept>

ModelView::TagInfo::TagInfo() : m_min(0), m_max(-1) {}

ModelView::TagInfo::TagInfo(std::string name, int min, int max, std::vector<std::string> modelTypes)
    : m_name(std::move(name)), m_min(min), m_max(max), m_modelTypes(std::move(modelTypes))
{
    if (m_min < 0 || (m_min > m_max && m_max >= 0) || m_name.empty()) {
        std::ostringstream ostr;
        ostr << "Invalid constructor parameters"
             << " " << m_name << " " << m_min << " " << m_max;
        throw std::runtime_error(ostr.str());
    }
}

ModelView::TagInfo ModelView::TagInfo::universalTag(std::string name,
                                                    std::vector<std::string> modelTypes)
{
    return TagInfo(std::move(name), 0, -1, std::move(modelTypes));
}

ModelView::TagInfo ModelView::TagInfo::propertyTag(std::string name, std::string model_type)
{
    return TagInfo(std::move(name), 1, 1, {std::move(model_type)});
}

std::string ModelView::TagInfo::name() const
{
    return m_name;
}

int ModelView::TagInfo::min() const
{
    return m_min;
}

int ModelView::TagInfo::max() const
{
    return m_max;
}

std::vector<std::string> ModelView::TagInfo::modelTypes() const
{
    return m_modelTypes;
}

//! Returns true if given modelType matches the list of possible model types.

bool ModelView::TagInfo::isValidChild(const std::string& modelType) const
{
    return m_modelTypes.empty() ? true : Utils::Contains(m_modelTypes, modelType);
}

//! Returns true if this tag is used to store single properties.
//! Properties are children that are created in SessionItem constructor using ::addProperty method.

bool ModelView::TagInfo::isSinglePropertyTag() const
{
    return m_min == 1 && m_max == 1;
}

bool ModelView::TagInfo::operator==(const ModelView::TagInfo& other) const
{
    return m_name == other.m_name && m_min == other.m_min && m_max == other.m_max
           && m_modelTypes == other.m_modelTypes;
}

bool ModelView::TagInfo::operator!=(const ModelView::TagInfo& other) const
{
    return !(*this == other);
}
