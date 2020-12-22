// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_FUNCTION_TYPES_H
#define MVVM_MODEL_FUNCTION_TYPES_H

#include <functional>
#include <memory>

namespace ModelView {

class SessionItem;

//! Definition for item factory funciton.
using item_factory_func_t = std::function<std::unique_ptr<SessionItem>()>;

//! Creates factory function for item of specific type.
template <typename T> item_factory_func_t ItemFactoryFunction()
{
    return []() { return std::make_unique<T>(); };
}

} // namespace ModelView

#endif // MVVM_MODEL_FUNCTION_TYPES_H
