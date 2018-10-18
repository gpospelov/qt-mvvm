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

#include "mvvm_types.h"

class SessionItem;

//! Interface class for all factories capable of producing SessionItem's.

class ItemFactoryInterface {
public:
    virtual ~ItemFactoryInterface() = default;

    virtual SessionItem* createItem(const model_type& modelType = {}) = 0;

    virtual SessionItem* createEmptyItem() = 0;

};

#endif
