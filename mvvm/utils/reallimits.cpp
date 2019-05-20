// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "reallimits.h"
#include "numericutils.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace
{
const double lmin = std::numeric_limits<double>::lowest();
const double lmax = std::numeric_limits<double>::max();
const double poszero = std::numeric_limits<double>::min();
} // namespace

using namespace ModelView;

RealLimits::RealLimits()
    : m_has_lower_limit(false), m_has_upper_limit(false), m_lower_limit(lmin), m_upper_limit(lmax)
{
}

RealLimits::RealLimits(bool has_lower_limit, bool has_upper_limit, double lower_limit,
                       double upper_limit)
    : m_has_lower_limit(has_lower_limit), m_has_upper_limit(has_upper_limit),
      m_lower_limit(lower_limit), m_upper_limit(upper_limit)
{
}

RealLimits RealLimits::lowerLimited(double bound_value)
{
    return RealLimits(true, false, bound_value, lmax);
}

RealLimits RealLimits::positive()
{
    return lowerLimited(poszero);
}

RealLimits RealLimits::nonnegative()
{
    return lowerLimited(0.);
}

RealLimits RealLimits::upperLimited(double bound_value)
{
    return RealLimits(false, true, lmin, bound_value);
}

RealLimits RealLimits::limited(double left_bound_value, double right_bound_value)
{
    return RealLimits(true, true, left_bound_value, right_bound_value);
}

RealLimits RealLimits::limitless()
{
    return RealLimits();
}

bool RealLimits::hasLowerLimit() const
{
    return m_has_lower_limit;
}

double RealLimits::lowerLimit() const
{
    return m_lower_limit;
}

bool RealLimits::hasUpperLimit() const
{
    return m_has_upper_limit;
}

double RealLimits::upperLimit() const
{
    return m_upper_limit;
}

bool RealLimits::hasLowerAndUpperLimits() const
{
    return (m_has_lower_limit && m_has_upper_limit);
}

bool RealLimits::isInRange(double value) const
{
    if (hasLowerLimit() && value < m_lower_limit)
        return false;
    if (hasUpperLimit() && value >= m_upper_limit)
        return false;
    return true;
}

bool RealLimits::operator==(const RealLimits& other) const
{
    return (m_has_lower_limit == other.m_has_lower_limit)
           && (m_has_upper_limit == other.m_has_upper_limit)
           && Utils::AreAlmostEqual(m_lower_limit, other.m_lower_limit)
           && Utils::AreAlmostEqual(m_upper_limit, other.m_upper_limit);
}

bool RealLimits::operator!=(const RealLimits& other) const
{
    return !(*this == other);
}

bool RealLimits::operator<(const RealLimits& other) const
{
    return m_lower_limit < other.m_lower_limit && m_upper_limit < other.m_upper_limit;
}

bool RealLimits::isLimitless() const
{
    return !hasLowerLimit() && !hasUpperLimit();
}

bool RealLimits::isPositive() const
{
    return hasLowerLimit() && !hasUpperLimit() && Utils::AreAlmostEqual(lowerLimit(), poszero) && lowerLimit() > 0.0;
}

bool RealLimits::isNonnegative() const
{
    return hasLowerLimit() && !hasUpperLimit() && Utils::AreAlmostEqual(lowerLimit(), 0.0);
}

bool RealLimits::isLowerLimited() const
{
    return hasLowerLimit() && !hasUpperLimit();
}

bool RealLimits::isUpperLimited() const
{
    return !hasLowerLimit() && hasUpperLimit();
}

bool RealLimits::isLimited() const
{
    return hasLowerLimit() && hasUpperLimit();
}
