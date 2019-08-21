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

#include "mvvm_export.h"

namespace ModelView
{

namespace Utils {

//! Returns true if two doubles agree within epsilon*tolerance.
bool CORE_EXPORT AreAlmostEqual(double a, double b, double tolerance_factor=1.0);

}

} // namespace ModelView

#endif // MVVM_NUMERICUTILS_H
