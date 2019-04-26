// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMPOOL_H
#define MVVM_ITEMPOOL_H

#include "mvvm_global.h"
#include "mvvm_types.h"
#include <map>

namespace ModelView {

class SessionItem;

//! Provides registration of SessionItem pointers and their unique identifiers
//! in global memory pool.

class CORE_EXPORT ItemPool
{
public:
    ItemPool() = default;
    ItemPool(const ItemPool&) = delete;
    ItemPool(ItemPool&&) = delete;
    ItemPool& operator=(const ItemPool&) = delete;
    ItemPool& operator=(ItemPool&&) = delete;

    static identifier_type generate_key();

    size_t size() const;

    identifier_type register_item(SessionItem* item, identifier_type key = {});
    void unregister_item(SessionItem* item);

    identifier_type key_for_item(SessionItem* item) const;

    SessionItem* item_for_key(const identifier_type& key) const;

private:
    std::map<identifier_type, SessionItem*> m_key_to_item;
    std::map<SessionItem*, identifier_type> m_item_to_key;
};

}  // namespace ModelView

#endif // MVVM_ITEMPOOL_H

