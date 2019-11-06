// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/model/itemmanager.h>
#include <mvvm/model/itemfactory.h>
#include <mvvm/model/itempool.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/standarditems/standarditemcatalogue.h>

namespace
{
std::unique_ptr<ModelView::ItemFactory> DefaultItemFactory()
{
    return std::make_unique<ModelView::ItemFactory>(ModelView::CreateStandardItemCatalogue());
}
} // namespace

using namespace ModelView;

ItemManager::ItemManager() : m_item_factory(DefaultItemFactory()) {}

void ItemManager::setItemFactory(std::unique_ptr<ItemFactoryInterface> factory)
{
    m_item_factory = std::move(factory);
}

void ItemManager::setItemPool(std::shared_ptr<ItemPool> pool)
{
    m_item_pool = std::move(pool);
}

ItemManager::~ItemManager() = default;

std::unique_ptr<SessionItem> ItemManager::createItem(const model_type& modelType) const
{
    return m_item_factory->createItem(modelType);
}

std::unique_ptr<SessionItem> ItemManager::createRootItem() const
{
    return m_item_factory->createEmptyItem();
}

SessionItem* ItemManager::findItem(const identifier_type& id) const
{
    return m_item_pool ? m_item_pool->item_for_key(id) : nullptr;
}

identifier_type ItemManager::findIdentifier(SessionItem* item) const
{
    return m_item_pool ? m_item_pool->key_for_item(item) : identifier_type();
}

const ItemPool* ItemManager::itemPool() const
{
    return m_item_pool.get();
}

ItemPool* ItemManager::itemPool()
{
    return m_item_pool.get();
}

void ItemManager::register_item(SessionItem* item)
{
    if (m_item_pool)
        m_item_pool->register_item(item, item->identifier());
}

void ItemManager::unregister_item(SessionItem* item)
{
    if (m_item_pool)
        m_item_pool->unregister_item(item);
}

//! Replacing existing registration in item pool with new id.

void ItemManager::fix_registration(SessionItem* item, const identifier_type& id)
{
    m_item_pool->unregister_item(item);
    m_item_pool->register_item(item, id);
}

const ItemFactoryInterface* ItemManager::factory() const
{
    return m_item_factory.get();
}
