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

ItemFactory::ItemFactory()
    : m_item_pool(new ItemPool)
{

}

SessionItem* ItemFactory::createItem(const model_type& modelType)
{
    auto result = new SessionItem(modelType);
    result->register_item(m_item_pool);
    return result;
}

SessionItem* ItemFactory::createEmptyItem()
{
    auto result = new SessionItem;
    result->register_item(m_item_pool);
    return result;
}

SessionItem* ItemFactory::findItem(identifier_type id) const
{
    return m_item_pool->item_for_key(id);
}

identifier_type ItemFactory::findIdentifier(SessionItem* item) const
{
    return m_item_pool->key_for_item(item);
}

const ItemPool& ItemFactory::itemPool() const
{
    return *m_item_pool.get();
}
