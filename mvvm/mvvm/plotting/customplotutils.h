// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CUSTOMPLOTUTILS_H
#define MVVM_CUSTOMPLOTUTILS_H

#include <mvvm/model/mvvm_export.h>

class QCPColorScale;
class QCPAxis;

namespace ModelView
{

class SessionItem;

namespace Utils
{

//! Switch axis to logarithmic scale mode.

CORE_EXPORT void SetLogarithmicScale(QCPColorScale* axis, bool is_log_scale);

//! Switch axis to logarithmic scale mode.

CORE_EXPORT void SetLogarithmicScale(QCPAxis* axis, bool isLogz);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_CUSTOMPLOTUTILS_H
