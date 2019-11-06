// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMMANAGER_H
#define MVVM_ITEMMANAGER_H

#include <mvvm/core/export.h>
#include <mvvm/model/mvvm_types.h>
#include <memory>

namespace ModelView
{

class SessionItem;
class ItemPool;
class ItemFactoryInterface;

//! Manages item creation/registration for SessionModel.

class CORE_EXPORT ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    void setItemFactory(std::unique_ptr<ItemFactoryInterface> factory);
    void setItemPool(std::shared_ptr<ItemPool> pool);

    std::unique_ptr<SessionItem> createItem(const model_type& modelType = {}) const;

    std::unique_ptr<SessionItem> createRootItem() const;

    SessionItem* findItem(const identifier_type& id) const;

    identifier_type findIdentifier(SessionItem* item) const;

    const ItemPool* itemPool() const;
    ItemPool* itemPool();

    void register_item(SessionItem* item);
    void unregister_item(SessionItem* item);

    void fix_registration(SessionItem* item, const identifier_type& id);

    const ItemFactoryInterface* factory() const;

private:
    std::shared_ptr<ItemPool> m_item_pool;
    std::unique_ptr<ItemFactoryInterface> m_item_factory;
};

} // namespace ModelView

#endif // MVVM_ITEMMANAGER_H
