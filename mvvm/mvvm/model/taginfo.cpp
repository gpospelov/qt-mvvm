// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/model/taginfo.h>
#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace
{
template <typename A, typename B> bool contains(const A& container, const B& element)
{
    return std::find(container.begin(), container.end(), element) != container.end();
}
} // namespace

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

bool ModelView::TagInfo::isValidChild(const std::string& child) const
{
    return m_modelTypes.empty() ? true : contains(m_modelTypes, child);
}

bool ModelView::TagInfo::isSinglePropertyTag() const
{
    return m_min == 1 && m_max == 1;
}

std::string ModelView::TagInfo::toString() const
{
    std::ostringstream ostr;
    ostr << "TagInfo> name:'" << name() << "', min:" << min() << ", max:" << max()
         << ", modelTypes:{";
    for (const auto& model_type : modelTypes()) {
        ostr << model_type << " ";
    }
    ostr << "}";
    return ostr.str();
}
