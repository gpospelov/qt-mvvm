// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_NUMERICUTILS_H
#define MVVM_UTILS_NUMERICUTILS_H

#include "mvvm/model_export.h"

namespace ModelView::Utils {

//! Returns true if two doubles agree within epsilon*tolerance.
MVVM_MODEL_EXPORT bool AreAlmostEqual(double a, double b, double tolerance_factor = 1.0);

//! Produces random integer values uniformly distributed on the closed interval [low, high].
MVVM_MODEL_EXPORT int RandInt(int low, int high);

//! Produces random FLOAT values uniformly distributed on the  interval [low, high).
MVVM_MODEL_EXPORT double RandDouble(double low, double high);

} // namespace ModelView::Utils

#endif // MVVM_UTILS_NUMERICUTILS_H
