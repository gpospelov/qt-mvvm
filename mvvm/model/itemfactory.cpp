// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemfactory.h"
#include "sessionitem.h"

SessionItem* ItemFactory::createItem(const model_type&)
{
    auto result = new SessionItem;
    m_item_pool.register_item(result);
    return result;
}

SessionItem* ItemFactory::createEmptyItem()
{
    auto result = new SessionItem;
    m_item_pool.register_item(result);
    return result;
}

SessionItem* ItemFactory::findItem(identifier_type id) const
{
    return m_item_pool.item_for_key(id);
}

identifier_type ItemFactory::findIdentifier(SessionItem* item) const
{
    return m_item_pool.key_for_item(item);
}

void ItemFactory::forgetItem(SessionItem* item)
{
    m_item_pool.deregister_item(item);
}

const ItemPool& ItemFactory::itemPool() const
{
    return m_item_pool;
}
