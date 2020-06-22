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

#include <algorithm>
#include <complex>
#include <iterator>
#include <memory>
#include <mvvm_model_export.h>
#include <string>
#include <type_traits>
#include <vector>

namespace ModelView
{

namespace Utils
{

template <class T> struct is_unique_ptr : std::false_type {
};

template <class T, class D> struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type {
};

//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1. Works with containers containing unique_ptr.

template <typename It, typename T> int IndexOfItem(It begin, It end, const T& item)
{
    It pos;
    if constexpr (is_unique_ptr<typename std::iterator_traits<It>::value_type>::value)
        pos = find_if(begin, end, [&item](const auto& x) { return x.get() == item; });
    else
        pos = find_if(begin, end, [&item](const auto& x) { return x == item; });

    return pos == end ? -1 : static_cast<int>(std::distance(begin, pos));
}

//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1. Works with containers containing unique_ptr.

template <typename C, typename T> int IndexOfItem(const C& container, const T& item)
{
    return IndexOfItem(container.begin(), container.end(), item);
}

//! Returns vector containing results of elemntwise unary function application.

template <typename It, typename UnaryFunction>
std::vector<double> Apply(It begin, It end, UnaryFunction func)
{
    std::vector<double> result;
    std::transform(begin, end, std::back_inserter(result), func);
    return result;
}

//! Returns vector with real part of complex numbers.

template <typename C> std::vector<double> Real(const C& container)
{
    return Apply(std::begin(container), std::end(container),
                 [](const auto& x) { return std::real(x); });
}

//! Returns vector with imag part of complex numbers.

template <typename C> std::vector<double> Imag(const C& container)
{
    return Apply(std::begin(container), std::end(container),
                 [](const auto& x) { return std::imag(x); });
}

} // namespace Utils

} // namespace ModelView

#endif // MVVM_UTILS_CONTAINERUTILS_H
