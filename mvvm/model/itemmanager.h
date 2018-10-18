// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <string>
#include <memory>
#include "mvvm_types.h"

class SessionItem;
class ItemPool;
class ItemFactoryInterface;
class JsonModelInterface;

//! Manages item creation/registration for SessionModel.

class ItemManager {
public:
    ItemManager();
    ~ItemManager();

    void setItemPool(std::shared_ptr<ItemPool> pool);

    SessionItem* createItem(const model_type& modelType = {});

    SessionItem* createRootItem();

    SessionItem* findItem(identifier_type id) const;

    identifier_type findIdentifier(SessionItem* item) const;

    const ItemPool* itemPool() const;

    const JsonModelInterface& converter() const;

private:
    std::shared_ptr<ItemPool> m_item_pool;
    std::unique_ptr<ItemFactoryInterface> m_item_factory;
    std::unique_ptr<JsonModelInterface> m_converter;
};

#endif
