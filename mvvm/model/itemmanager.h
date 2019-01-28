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

#include "global.h"
#include "model_types.h"
#include <string>
#include <memory>

namespace ModelView {

class SessionItem;
class ItemPool;
class ItemFactoryInterface;
class JsonModelInterface;

//! Manages item creation/registration for SessionModel.

class CORE_EXPORT ItemManager {
public:
    ItemManager();
    ~ItemManager();

    void setItemFactory(std::unique_ptr<ItemFactoryInterface> factory);
    void setItemPool(std::shared_ptr<ItemPool> pool);

    SessionItem* createItem(const model_type& modelType = {});

    SessionItem* createRootItem();

    SessionItem* findItem(const identifier_type& id) const;

    identifier_type findIdentifier(SessionItem* item) const;

    const ItemPool* itemPool() const;
    ItemPool* itemPool();

    const JsonModelInterface& converter() const;

    void fix_registration(SessionItem* item, const identifier_type& id);

private:
    std::shared_ptr<ItemPool> m_item_pool;
    std::unique_ptr<ItemFactoryInterface> m_item_factory;
    std::unique_ptr<JsonModelInterface> m_converter;
};

}  // namespace ModelView

#endif
