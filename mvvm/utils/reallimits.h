// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_REALLIMITS_H
#define MVVM_REALLIMITS_H

#include "mvvm_global.h"
#include <sstream>
#include <string>

namespace ModelView
{

//! Limits for double.
//! @ingroup fitting

class CORE_EXPORT RealLimits
{
public:
    RealLimits();

    //! if has lower limit
    bool hasLowerLimit() const;

    //! Returns lower limit
    double lowerLimit() const;

    //! Sets lower limit
    void setLowerLimit(double value);

    //! remove lower limit
    void removeLowerLimit();

    //! if has upper limit
    bool hasUpperLimit() const;

    //! Returns upper limit
    double upperLimit() const;

    //! Sets upper limit
    void setUpperLimit(double value);

    //! remove upper limit
    void removeUpperLimit();

    //! if has lower and upper limit
    bool hasLowerAndUpperLimits() const;

    //! Sets lower and upper limits
    void setLimits(double xmin, double xmax);

    //! remove limits
    void removeLimits();

    //! returns true if proposed value is in limits range
    bool isInRange(double value) const;

    //! Creates an object bounded from the left
    static RealLimits lowerLimited(double bound_value);

    //! Creates an object which can have only positive values (>0., zero is not included)
    static RealLimits positive();

    //! Creates an object which can have only positive values with 0. included
    static RealLimits nonnegative();

    //! Creates an object bounded from the right
    static RealLimits upperLimited(double bound_value);

    //! Creates an object bounded from the left and right
    static RealLimits limited(double left_bound_value, double right_bound_value);

    //! Creates an object withoud bounds (default)
    static RealLimits limitless();

    std::string toString() const;

    //! Prints class
    friend std::ostream& operator<<(std::ostream& ostr, const RealLimits& m)
    {
        ostr << m.toString();
        return ostr;
    }

    bool operator==(const RealLimits& other) const;
    bool operator!=(const RealLimits& other) const;

    bool isLimitless() const;
    bool isPositive() const;
    bool isNonnegative() const;
    bool isLowerLimited() const;
    bool isUpperLimited() const;
    bool isLimited() const;

protected:
    RealLimits(bool has_lower_limit, bool has_upper_limit, double lower_limit, double upper_limit);

    bool m_has_lower_limit; //! parameter has lower bound
    bool m_has_upper_limit; //! parameter has upper bound
    double m_lower_limit;   //! minimum allowed value
    double m_upper_limit;   //! maximum allowed value
};

} // namespace ModelView

#endif // MVVM_REALLIMITS_H
