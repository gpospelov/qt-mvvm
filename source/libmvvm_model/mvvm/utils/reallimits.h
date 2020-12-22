// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_REALLIMITS_H
#define MVVM_UTILS_REALLIMITS_H

#include "mvvm/model_export.h"

namespace ModelView {

//! Limits for double value.

class MVVM_MODEL_EXPORT RealLimits {
public:
    RealLimits();

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

    //! if has lower limit
    bool hasLowerLimit() const;

    //! Returns lower limit
    double lowerLimit() const;

    //! if has upper limit
    bool hasUpperLimit() const;

    //! Returns upper limit
    double upperLimit() const;

    //! if has lower and upper limit
    bool hasLowerAndUpperLimits() const;

    //! returns true if proposed value is in limits range
    bool isInRange(double value) const;

    bool operator==(const RealLimits& other) const;
    bool operator!=(const RealLimits& other) const;
    bool operator<(const RealLimits& other) const;

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

#endif // MVVM_UTILS_REALLIMITS_H
