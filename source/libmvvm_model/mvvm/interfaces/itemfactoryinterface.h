// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_ITEMFACTORYINTERFACE_H
#define MVVM_INTERFACES_ITEMFACTORYINTERFACE_H

#include "mvvm/core/types.h"
#include "mvvm/model/function_types.h"
#include "mvvm/model_export.h"
#include <memory>

namespace ModelView {

class SessionItem;

//! Interface class for all factories capable of producing SessionItem's.

class MVVM_MODEL_EXPORT ItemFactoryInterface {
public:
    virtual ~ItemFactoryInterface() = default;

    virtual void registerItem(const std::string& modelType, item_factory_func_t func,
                              const std::string& label) = 0;

    virtual std::unique_ptr<SessionItem> createItem(const model_type& modelType) const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ITEMFACTORYINTERFACE_H
