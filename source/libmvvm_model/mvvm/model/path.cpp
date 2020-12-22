// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/path.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <sstream>

using namespace ModelView;

//! Constructs Path object from string containing sequence of integers ("0,0,1,3").

Path Path::fromString(const std::string& str)
{
    Path result;

    std::string str_spaces(str);
    std::replace(str_spaces.begin(), str_spaces.end(), ',', ' ');

    std::istringstream iss(str_spaces);
    std::for_each(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
                  [&result](auto x) { result.append(std::stoi(x)); });
    return result;
}

//! Constructs Path object from vector of integers..

Path Path::fromVector(const std::vector<int>& data)
{
    Path result;
    std::for_each(data.begin(), data.end(), [&result](auto x) { result.append(x); });
    return result;
}

//! Returns string representing path ("0,0,1,3").

std::string Path::str() const
{
    auto comma_fold = [](std::string a, int b) { return std::move(a) + ',' + std::to_string(b); };
    return m_data.empty() ? std::string()
                          : std::accumulate(std::next(m_data.begin()), m_data.end(),
                                            std::to_string(m_data[0]), comma_fold);
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
