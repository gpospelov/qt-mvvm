// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMFACTORYINTERFACE_H
#define ITEMFACTORYINTERFACE_H

#include "global.h"
#include "model_types.h"
#include <memory>

namespace ModelView
{

class SessionItem;

//! Interface class for all factories capable of producing SessionItem's.

class CORE_EXPORT ItemFactoryInterface
{
public:
    virtual ~ItemFactoryInterface() = default;

    virtual std::unique_ptr<SessionItem> createItem(const model_type& modelType = {}) const = 0;

    virtual std::unique_ptr<SessionItem> createEmptyItem() const = 0;
};

} // namespace ModelView

#endif
