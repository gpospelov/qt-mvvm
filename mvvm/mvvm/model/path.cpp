// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/model/path.h>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace ModelView;

Path Path::fromString(const std::string& str)
{
    Path result;

    std::string str_spaces(str);
    std::replace( str_spaces.begin(), str_spaces.end(), ',', ' ');

    std::vector<std::string> parts;

    std::istringstream iss(str_spaces);
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(parts));

    for (const auto& x : parts)
        result.append(std::stoi(x));

    return result;
}

Path Path::fromVector(const std::vector<int>& data)
{
    Path result;

    for(auto x : data)
        result.append(x);

    return result;
}

std::string Path::str()
{
    std::ostringstream str;
    std::string result;

    for(auto it = m_data.begin(); it!= m_data.end(); ++it) {
        str << std::to_string(*it);
        if (std::next(it) != m_data.end())
            str << ",";
    }

    return str.str();
}

void Path::append(Path::PathElement element)
{
    m_data.push_back(element);
}

void Path::prepend(Path::PathElement element)
{
    m_data.insert(m_data.begin(), element);
}

Path::iterator Path::begin()
{
    return m_data.begin();
}

Path::const_iterator Path::begin() const
{
    return m_data.begin();
}

Path::iterator Path::end()
{
    return m_data.end();
}

Path::const_iterator Path::end() const
{
    return m_data.end();
}
