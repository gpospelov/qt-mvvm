// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_SIGNALS_CALLBACK_TYPES_H
#define MVVM_SIGNALS_CALLBACK_TYPES_H

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

#endif  // MVVM_SIGNALS_CALLBACK_TYPES_H

