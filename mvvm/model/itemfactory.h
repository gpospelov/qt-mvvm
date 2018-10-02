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

class SessionItem;

class ItemFactory {
public:
    SessionItem* createItem(const model_type& modelType = {});

    SessionItem* createEmptyItem();

    SessionItem* findItem(identifier_type id) const;

    identifier_type findIdentifier(SessionItem* item) const;

    void forgetItem(SessionItem* item);

    const ItemPool& itemPool() const;

private:
    ItemPool m_item_pool;
};

#endif
