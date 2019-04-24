// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PATH_H
#define MVVM_PATH_H

#include "global.h"
#include <vector>
#include <string>

namespace ModelView {

//! Provides navigation through SessionModel.
//! Contains chain of row indexes which has to be used to reach desired SessionItem starting
//! from root item.

class CORE_EXPORT Path
{
public:
    using PathElement = int;
    using container_t = std::vector<PathElement>;
    using iterator = container_t::iterator;
    using const_iterator = container_t::const_iterator;

    Path() = default;

    static Path fromString(const std::string& str);

    static Path fromVector(const std::vector<int>& data);

    std::string str();

    void append(PathElement element);
    void prepend(PathElement element);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    container_t m_data;
};

}  // namespace ModelView

#endif // MVVM_PATH_H

