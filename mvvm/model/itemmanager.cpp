// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemmanager.h"
#include "sessionitem.h"
#include "itempool.h"
#include "itemfactory.h"

ItemManager::ItemManager()
    : m_item_pool(new ItemPool)
    , m_item_factory(new ItemFactory)
{

}

ItemManager::~ItemManager() = default;

SessionItem* ItemManager::createItem(const model_type& modelType)
{
    auto result = m_item_factory->createItem(modelType);
    result->register_item(m_item_pool);
    return result;
}

SessionItem* ItemManager::createRootItem()
{
    auto result = m_item_factory->createEmptyItem();
    result->register_item(m_item_pool);
    return result;
}

SessionItem* ItemManager::findItem(identifier_type id) const
{
    return m_item_pool->item_for_key(id);
}

identifier_type ItemManager::findIdentifier(SessionItem* item) const
{
    return m_item_pool->key_for_item(item);
}

const ItemPool& ItemManager::itemPool() const
{
    return *m_item_pool.get();
}
