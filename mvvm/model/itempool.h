// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMPOOL_H
#define ITEMPOOL_H

#include <map>
#include "model_types.h"

class SessionItem;

//! Provides registration of SessionItem pointers and their unique identifiers
//! in global memory pool.

class ItemPool
{
public:
    using key_type = identifier_type;

    ItemPool() = default;
    ItemPool(const ItemPool&) = delete;
    ItemPool(ItemPool&&) = delete;
    ItemPool& operator=(const ItemPool&) = delete;
    ItemPool& operator=(ItemPool&&) = delete;

    static key_type generate_key();

    size_t size() const;

    key_type register_item(SessionItem* item, key_type = {});
    void deregister_item(SessionItem* item);

    key_type key_for_item(SessionItem* item) const;

    SessionItem* item_for_key(key_type) const;

private:
    std::map<key_type, SessionItem*> m_key_to_item;
    std::map<SessionItem*, key_type> m_item_to_key;
};

#endif
