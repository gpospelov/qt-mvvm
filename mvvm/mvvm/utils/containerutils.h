// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CONTAINERUTILS_H
#define MVVM_CONTAINERUTILS_H

#include "mvvm_export.h"
#include <string>
#include <iterator>

namespace ModelView {

namespace Utils {

//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1.

template <typename C, typename T> int IndexOfItem(const C& container, const T& item)
{
    auto pos = find(container.begin(), container.end(), item);
    return pos == container.end() ? -1 : static_cast<int>(std::distance(container.begin(), pos));
}

}  // namespace Utils

}  // namespace ModelView

#endif // MVVM_CONTAINERUTILS_H

