// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_JSONUTILS_H
#define MVVM_JSONUTILS_H

#include "mvvm_global.h"
#include <string>

class QJsonObject;

namespace ModelView {

class SessionModel;
class RealLimits;

namespace JsonUtils {

//! Returns multiline string representing model content as json.
CORE_EXPORT std::string ModelToJsonString(const SessionModel& model);

//! Returns string representation of RealLimits.
CORE_EXPORT std::string ToString(const RealLimits& limits);

CORE_EXPORT RealLimits CreateLimits(const std::string& text, double min = 0.0, double max = 0.0);

} // JsonUtils

} // ModelView

#endif // MVVM_JSONUTILS_H
