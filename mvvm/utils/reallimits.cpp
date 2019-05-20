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
const std::string text_limitless = "limitless";
const std::string text_positive = "positive";
const std::string text_nonnegative = "nonnegative";
const std::string text_lowerlimited = "lowerlimited";
const std::string text_upperlimited = "upperlimited";
const std::string text_limited = "limited";
const std::string separator = " ";
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

//! Returns text representing RealLimits.

std::string RealLimits::text() const
{
    std::stringstream sstr;

    if (isLimitless())
        sstr << text_limitless;
    else if (isPositive())
        sstr << text_positive;
    else if (isNonnegative())
        sstr << text_nonnegative;
    else if(isLowerLimited())
        sstr << text_lowerlimited << separator << m_lower_limit;
    else if(isUpperLimited())
        sstr << text_upperlimited << separator << m_upper_limit;
    else if(isLimited())
        sstr << text_limited << separator << m_lower_limit << separator << m_upper_limit;
    else
        throw std::runtime_error("RealLimits::text() -> Unknown type");

    return sstr.str();
}

//! Constructs RealLimits from its text representation.

RealLimits RealLimits::fromText(const std::string& text)
{
    std::string kind;
    double val1(0), val2(0);

    std::stringstream sstr(text);
    sstr >> kind >> val1 >> val2;

    if (kind == text_limitless)
        return RealLimits();
    else if (kind == text_positive)
        return RealLimits::positive();
    else if (kind == text_nonnegative)
        return RealLimits::nonnegative();
    else if(kind == text_lowerlimited)
        return RealLimits::lowerLimited(val1);
    else if(kind == text_upperlimited)
        return RealLimits::upperLimited(val1);
    else if(kind == text_limited)
        return RealLimits::limited(val1, val2);
    else
        throw std::runtime_error("RealLimits::fromText() -> Unknown type");
}





