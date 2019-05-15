// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "reallimits.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace ModelView;

RealLimits::RealLimits()
    : m_has_lower_limit(false), m_has_upper_limit(false), m_lower_limit(0.), m_upper_limit(0.)
{
}

RealLimits::RealLimits(bool has_lower_limit, bool has_upper_limit, double lower_limit,
                       double upper_limit)
    : m_has_lower_limit(has_lower_limit), m_has_upper_limit(has_upper_limit),
      m_lower_limit(lower_limit), m_upper_limit(upper_limit)
{
}

bool RealLimits::hasLowerLimit() const
{
    return m_has_lower_limit;
}

double RealLimits::lowerLimit() const
{
    return m_lower_limit;
}

void RealLimits::setLowerLimit(double value)
{
    m_lower_limit = value;
    m_has_lower_limit = true;
}

void RealLimits::removeLowerLimit()
{
    m_lower_limit = 0.;
    m_has_lower_limit = false;
}

bool RealLimits::hasUpperLimit() const
{
    return m_has_upper_limit;
}

double RealLimits::upperLimit() const
{
    return m_upper_limit;
}

void RealLimits::setUpperLimit(double value)
{
    m_upper_limit = value;
    m_has_upper_limit = true;
}

void RealLimits::removeUpperLimit()
{
    m_upper_limit = 0.;
    m_has_upper_limit = false;
}

bool RealLimits::hasLowerAndUpperLimits() const
{
    return (m_has_lower_limit && m_has_upper_limit);
}

void RealLimits::setLimits(double xmin, double xmax)
{
    setLowerLimit(xmin);
    setUpperLimit(xmax);
}

void RealLimits::removeLimits()
{
    removeLowerLimit();
    removeUpperLimit();
}

bool RealLimits::isInRange(double value) const
{
    if (hasLowerLimit() && value < m_lower_limit)
        return false;
    if (hasUpperLimit() && value >= m_upper_limit)
        return false;
    return true;
}

RealLimits RealLimits::lowerLimited(double bound_value)
{
    return RealLimits(true, false, bound_value, 0.);
}

RealLimits RealLimits::positive()
{
    return lowerLimited(std::numeric_limits<double>::min());
}

RealLimits RealLimits::nonnegative()
{
    return lowerLimited(0.);
}

RealLimits RealLimits::upperLimited(double bound_value)
{
    return RealLimits(false, true, 0., bound_value);
}

RealLimits RealLimits::limited(double left_bound_value, double right_bound_value)
{
    return RealLimits(true, true, left_bound_value, right_bound_value);
}

RealLimits RealLimits::limitless()
{
    return RealLimits();
}

std::string RealLimits::toString() const
{
    std::ostringstream result;

    if (isLimitless())
        result << "unlimited";

    else if (isPositive())
        result << "positive";

    else if (isNonnegative())
        result << "nonnegative";

    else if (isLowerLimited())
        result << "lowerLimited(" << std::fixed << std::setprecision(2) << lowerLimit() << ")";

    else if (isUpperLimited())
        result << "upperLimited(" << std::fixed << std::setprecision(2) << upperLimit() << ")";

    else if (isLimited())
        result << "limited(" << std::fixed << std::setprecision(2) << lowerLimit() << ","
               << std::fixed << std::setprecision(2) << upperLimit() << ")";

    return result.str();
}

bool RealLimits::operator==(const RealLimits& other) const
{
    return (m_has_lower_limit == other.m_has_lower_limit)
           && (m_has_upper_limit == other.m_has_upper_limit)
           && (m_lower_limit == other.m_lower_limit) && (m_upper_limit == other.m_upper_limit);
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
    return hasLowerLimit() && !hasUpperLimit()
           && lowerLimit() == std::numeric_limits<double>::min();
}

bool RealLimits::isNonnegative() const
{
    return hasLowerLimit() && !hasUpperLimit() && lowerLimit() == 0.0;
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
