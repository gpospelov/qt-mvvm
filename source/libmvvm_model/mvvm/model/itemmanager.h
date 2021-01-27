// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMMANAGER_H
#define MVVM_MODEL_ITEMMANAGER_H

#include "mvvm/core/types.h"
#include "mvvm/model_export.h"
#include <memory>

namespace ModelView {

class SessionItem;
class ItemPool;
class ItemFactoryInterface;

//! Manages item creation/registration for SessionModel.

class MVVM_MODEL_EXPORT ItemManager {
public:
    ItemManager();
    ~ItemManager();

    void setItemFactory(std::unique_ptr<ItemFactoryInterface> factory);
    void setItemPool(std::shared_ptr<ItemPool> pool);

    std::unique_ptr<SessionItem> createItem(const model_type& modelType = {}) const;

    std::unique_ptr<SessionItem> createRootItem() const;

    SessionItem* findItem(const identifier_type& id) const;

    identifier_type findIdentifier(const SessionItem* item) const;

    const ItemPool* itemPool() const;
    ItemPool* itemPool();

    void registerInPool(SessionItem* item);
    void unregisterFromPool(SessionItem* item);

    const ItemFactoryInterface* factory() const;

    ItemFactoryInterface* factory();

private:
    std::shared_ptr<ItemPool> m_item_pool;
    std::unique_ptr<ItemFactoryInterface> m_item_factory;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMMANAGER_H
