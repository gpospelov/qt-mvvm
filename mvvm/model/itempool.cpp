// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itempool.h"
#include <QUuid>
#include <stdexcept>

ItemPool::key_type ItemPool::generate_key()
{
    return  QUuid::createUuid().toString().toStdString();
}

size_t ItemPool::size() const
{
    assert(m_key_to_item.size() == m_item_to_key.size());
    return m_key_to_item.size();
}

ItemPool::key_type ItemPool::register_item(SessionItem* item)

{
    if (m_item_to_key.find(item) != m_item_to_key.end())
        throw std::runtime_error("ItemPool::register_item() -> Attempt to register already "
                                 "registered item.");

    auto key = generate_key();
    while (m_key_to_item.find(key) != m_key_to_item.end())
        key = generate_key(); // preventing improbably duplicates

    m_key_to_item.insert(std::make_pair(key, item));
    m_item_to_key.insert(std::make_pair(item, key));

    return key;
}

void ItemPool::deregister_item(SessionItem* item)
{
    auto it = m_item_to_key.find(item);
    if ( it == m_item_to_key.end())
        throw std::runtime_error("ItemPool::deregister_item() -> Attempt to deregister "
                                 "non existing item.");
    auto key = it->second;
    m_item_to_key.erase(it);

    auto it2 = m_key_to_item.find(key);
    m_key_to_item.erase(it2);
}

ItemPool::key_type ItemPool::key_for_item(SessionItem* item) const
{
    auto it = m_item_to_key.find(item);
    if (it != m_item_to_key.end())
        return it->second;

    return {};
}

SessionItem* ItemPool::item_for_key(key_type key) const
{
    auto it = m_key_to_item.find(key);
    if (it != m_key_to_item.end())
        return it->second;

    return nullptr;
}
