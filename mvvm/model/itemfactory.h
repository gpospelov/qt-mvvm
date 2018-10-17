// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <string>
#include "mvvm_types.h"
#include "itempool.h"
#include <memory>

class SessionItem;

class ItemFactory {
public:
    ItemFactory();

    SessionItem* createItem(const model_type& modelType = {});

    SessionItem* createEmptyItem();

    SessionItem* findItem(identifier_type id) const;

    identifier_type findIdentifier(SessionItem* item) const;

    const ItemPool& itemPool() const;

private:
    std::shared_ptr<ItemPool> m_item_pool;
};

#endif
