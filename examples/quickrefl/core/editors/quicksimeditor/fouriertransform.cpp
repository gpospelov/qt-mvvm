// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "fouriertransform.h"
#include <algorithm>
#include <numeric>

//! Implementation of fourier transformation for vector with complex numbers.
//! Taken from C++ STL Cookbook by Jacek Galowicz.

class num_iterator
{
    size_t pos;

public:
    explicit num_iterator(size_t position) : pos(position) {}

    size_t operator*() const { return pos; }

    num_iterator& operator++()
    {
        ++pos;
        return *this;
    }

    bool operator!=(const num_iterator& other) const { return pos != other.pos; }
};

signal_t fourier_transform(const signal_t& signal, bool back_transform)
{
    signal_t result(signal.size());

    const double pol{2.0 * M_PI * (back_transform ? -1.0 : 1.0)};
    const double div{back_transform ? 1.0 : double(signal.size())};

    auto sum_up = [=, &signal](size_t j) {
        return [=, &signal](std::complex<double> c, size_t k) {
            return c + signal[k] * std::polar(1.0, pol * k * j / double(signal.size()));
        };
    };

    auto to_ft = [=, &signal](size_t j) {
        return std::accumulate(num_iterator{0}, num_iterator{signal.size()}, std::complex<double>{},
                               sum_up(j))
               / div;
    };

    std::transform(num_iterator{0}, num_iterator{signal.size()}, begin(result), to_ft);

    return result;
}
