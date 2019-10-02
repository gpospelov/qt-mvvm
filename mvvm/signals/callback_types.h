// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CALLBACK_TYPES_H
#define MVVM_CALLBACK_TYPES_H

#include <string>
#include <functional>

namespace ModelView {

class SessionItem;
class SessionModel;

namespace Callbacks {
using slot_t = const void*;
using item_t = std::function<void(SessionItem*)>;
using item_int_t = std::function<void(SessionItem*, int)>;
using item_str_t = std::function<void(SessionItem*, std::string)>;
using item_str_int_t = std::function<void(SessionItem*, std::string, int)>;
using model_t = std::function<void(SessionModel*)>;
}

} // namespace ModelView

#endif // MVVM_CALLBACK_TYPES_H

