// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef PATH_H
#define PATH_H

#include <vector>
#include <string>

class Path
{
public:
    using PathElement = int;

    Path() = default;

    std::string str();

    void append(PathElement element);

private:
    std::vector<PathElement> m_data;
};

#endif
