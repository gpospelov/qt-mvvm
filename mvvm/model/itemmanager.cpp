// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemmanager.h"
#include "customvariants.h"
#include "defaultitemcatalogue.h"
#include "itemfactory.h"
#include "itempool.h"
#include "jsonconverterinterfaces.h"
#include "jsonmodel.h"
#include "jsonitem.h"
#include "sessionitem.h"

namespace
{
std::unique_ptr<ModelView::ItemFactory> DefaultItemFactory()
{
    return std::make_unique<ModelView::ItemFactory>(ModelView::CreateDefaultItemCatalogue());
}
} // namespace

using namespace ModelView;

ItemManager::ItemManager() : m_item_factory(DefaultItemFactory()), m_converter(new JsonModel)
{
    m_item_converter = std::make_unique<JsonItem>(m_item_factory.get());
}

void ItemManager::setItemFactory(std::unique_ptr<ItemFactoryInterface> factory)
{
    m_item_factory = std::move(factory);
    m_item_converter = std::make_unique<JsonItem>(m_item_factory.get());
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

const JsonModelInterface& ItemManager::converter() const
{
    return *m_converter;
}

const JsonItemInterface& ItemManager::item_converter() const
{
    return *m_item_converter;
}

void ItemManager::register_item(SessionItem* item)
{
    if (m_item_pool)
        m_item_pool->register_item(item, item->data(ItemDataRole::IDENTIFIER).value<std::string>());
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
