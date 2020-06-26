// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMFACTORYINTERFACE_H
#define MVVM_MODEL_ITEMFACTORYINTERFACE_H

#include <memory>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model_export.h>

namespace ModelView
{

class SessionItem;

//! Interface class for all factories capable of producing SessionItem's.

class MVVM_MODEL_EXPORT ItemFactoryInterface
{
public:
    virtual ~ItemFactoryInterface() = default;

    virtual std::unique_ptr<SessionItem> createItem(const model_type& modelType) const = 0;

    virtual std::unique_ptr<SessionItem> createEmptyItem() const = 0;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMFACTORYINTERFACE_H
