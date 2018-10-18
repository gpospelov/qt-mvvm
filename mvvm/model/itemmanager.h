// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <string>
#include "mvvm_types.h"
#include "itempool.h"
#include <memory>

class SessionItem;

//! Manages item creation/registration for SessionModel.

class ItemManager {
public:
    ItemManager();

    SessionItem* createItem(const model_type& modelType = {});

    SessionItem* createEmptyItem();

    SessionItem* findItem(identifier_type id) const;

    identifier_type findIdentifier(SessionItem* item) const;

    const ItemPool& itemPool() const;

private:
    std::shared_ptr<ItemPool> m_item_pool;
};

#endif
