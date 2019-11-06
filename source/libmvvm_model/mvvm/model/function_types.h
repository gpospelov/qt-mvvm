// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
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

