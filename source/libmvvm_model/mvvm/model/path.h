// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_PATH_H
#define MVVM_MODEL_PATH_H

#include <mvvm/core/export.h>
#include <string>
#include <vector>

namespace ModelView
{

//! Supports navigation through SessionModel. It contains a chain of row indexes that have to
//! be used to reach the desired SessionItem starting from the root item.

class MVVM_MODEL_EXPORT Path
{
public:
    using PathElement = int;
    using container_t = std::vector<PathElement>;
    using iterator = container_t::iterator;
    using const_iterator = container_t::const_iterator;

    Path() = default;

    static Path fromString(const std::string& str);

    static Path fromVector(const std::vector<int>& data);

    std::string str() const;

    void append(PathElement element);
    void prepend(PathElement element);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    container_t m_data;
};

} // namespace ModelView

#endif // MVVM_MODEL_PATH_H
