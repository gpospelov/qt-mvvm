// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_CALLBACK_TYPES_H
#define MVVM_SIGNALS_CALLBACK_TYPES_H

#include "mvvm/model/tagrow.h"
#include <functional>
#include <string>

namespace ModelView {

class SessionItem;
class SessionModel;

namespace Callbacks {
using slot_t = const void*;
using item_t = std::function<void(SessionItem*)>;
using item_int_t = std::function<void(SessionItem*, int)>;
using item_str_t = std::function<void(SessionItem*, std::string)>;
using item_tagrow_t = std::function<void(SessionItem*, TagRow)>;
using model_t = std::function<void(SessionModel*)>;
} // namespace Callbacks

} // namespace ModelView

#endif // MVVM_SIGNALS_CALLBACK_TYPES_H
