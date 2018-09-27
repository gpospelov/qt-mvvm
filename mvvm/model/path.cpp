// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "path.h"
#include <sstream>

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
