// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "numericutils.h"
#include <cmath>
#include <limits>
#include <algorithm>

using namespace ModelView;

bool Utils::AreAlmostEqual(double a, double b, double tolerance)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    return std::abs(a-b) <= eps * std::max( tolerance*eps, std::max(1., tolerance)*std::abs(b) );
}
