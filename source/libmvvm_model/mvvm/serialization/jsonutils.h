// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONUTILS_H
#define MVVM_SERIALIZATION_JSONUTILS_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView {

class SessionModel;
class RealLimits;

namespace JsonUtils {

//! Returns multiline string representing model content as json.
MVVM_MODEL_EXPORT std::string ModelToJsonString(const SessionModel& model);

//! Returns string representation of RealLimits.
MVVM_MODEL_EXPORT std::string ToString(const RealLimits& limits);

MVVM_MODEL_EXPORT RealLimits CreateLimits(const std::string& text, double min = 0.0,
                                          double max = 0.0);

} // namespace JsonUtils

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONUTILS_H
