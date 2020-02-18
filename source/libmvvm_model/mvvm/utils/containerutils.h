// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_CONTAINERUTILS_H
#define MVVM_UTILS_CONTAINERUTILS_H

#include <iterator>
#include <mvvm/core/export.h>
#include <string>

namespace ModelView
{

namespace Utils
{

//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1.

template <typename C, typename T> int IndexOfItem(const C& container, const T& item)
{
    auto pos = find(container.begin(), container.end(), item);
    return pos == container.end() ? -1 : static_cast<int>(std::distance(container.begin(), pos));
}


//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1.

template <typename It, typename T> int IndexOfItem(It begin, It end, const T& item)
{
    auto pos = find(begin, end, item);
    return pos == end ? -1 : static_cast<int>(std::distance(begin, pos));
}


} // namespace Utils

} // namespace ModelView

#endif // MVVM_UTILS_CONTAINERUTILS_H
