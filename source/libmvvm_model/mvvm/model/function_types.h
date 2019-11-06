// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_MODEL_FUNCTION_TYPES_H
#define MVVM_MODEL_FUNCTION_TYPES_H

#include <memory>
#include <functional>

namespace ModelView {

class SessionItem;
using item_factory_func_t = std::function<std::unique_ptr<SessionItem>()>;

} // namespace ModelView

#endif  // MVVM_MODEL_FUNCTION_TYPES_H

