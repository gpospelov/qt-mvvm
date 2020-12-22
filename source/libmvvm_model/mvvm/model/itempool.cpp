// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/itempool.h"
#include "mvvm/core/uniqueidgenerator.h"
#include <stdexcept>

using namespace ModelView;

size_t ItemPool::size() const
{
    if (m_key_to_item.size() != m_item_to_key.size())
        throw std::runtime_error("Error in ItemPool: array size mismatch");
    return m_key_to_item.size();
}

identifier_type ItemPool::register_item(SessionItem* item, identifier_type key)

{
    if (m_item_to_key.find(item) != m_item_to_key.end())
        throw std::runtime_error("ItemPool::register_item() -> Attempt to register already "
                                 "registered item.");

    if (key.empty()) {
        key = UniqueIdGenerator::generate();
        while (m_key_to_item.find(key) != m_key_to_item.end())
            key = UniqueIdGenerator::generate(); // preventing improbable duplicates
    }
    else {
        if (m_key_to_item.find(key) != m_key_to_item.end())
            throw std::runtime_error(" ItemPool::register_item() -> Attempt to reuse existing key");
    }

    m_key_to_item.insert(std::make_pair(key, item));
    m_item_to_key.insert(std::make_pair(item, key));

    return key;
}

void ItemPool::unregister_item(SessionItem* item)
{
    auto it = m_item_to_key.find(item);
    if (it == m_item_to_key.end())
        throw std::runtime_error("ItemPool::deregister_item() -> Attempt to deregister "
                                 "non existing item.");
    auto key = it->second;
    m_item_to_key.erase(it);

    auto it2 = m_key_to_item.find(key);
    m_key_to_item.erase(it2);
}

identifier_type ItemPool::key_for_item(const SessionItem* item) const
{
    const auto it = m_item_to_key.find(item);
    if (it != m_item_to_key.end())
        return it->second;

    return {};
}

SessionItem* ItemPool::item_for_key(const identifier_type& key) const
{
    auto it = m_key_to_item.find(key);
    if (it != m_key_to_item.end())
        return it->second;

    return nullptr;
}
