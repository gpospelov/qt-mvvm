// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_NUMERICUTILS_H
#define MVVM_NUMERICUTILS_H

#include <mvvm/model/mvvm_export.h>

namespace ModelView
{

namespace Utils {

//! Returns true if two doubles agree within epsilon*tolerance.
CORE_EXPORT bool AreAlmostEqual(double a, double b, double tolerance_factor=1.0);

//! Produces random integer values uniformly distributed on the closed interval [low, high].
CORE_EXPORT int RandInt(int low, int high);

//! Produces random FLOAT values uniformly distributed on the  interval [low, high).
CORE_EXPORT double RandDouble(double low, double high);

}

} // namespace ModelView

#endif // MVVM_NUMERICUTILS_H
