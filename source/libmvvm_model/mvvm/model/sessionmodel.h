// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_SESSIONMODEL_H
#define MVVM_MODEL_SESSIONMODEL_H

#include "mvvm/core/types.h"
#include "mvvm/core/variant.h"
#include "mvvm/model/function_types.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/tagrow.h"
#include "mvvm/model_export.h"
#include <memory>

namespace ModelView {

class SessionItem;
class ItemCatalogue;
class ItemPool;
class ModelMapper;
class ItemFactoryInterface;
class UndoStackInterface;

//! Main class to hold hierarchy of SessionItem objects.

class MVVM_MODEL_EXPORT SessionModel {
public:
    explicit SessionModel(std::string model_type = {}, std::shared_ptr<ItemPool> pool = {});
    virtual ~SessionModel();
    SessionModel(const SessionModel& other) = delete;
    SessionModel& operator=(const SessionModel& other) = delete;

    // Methods to manipulate data and items.

    SessionItem* insertNewItem(const model_type& modelType, SessionItem* parent = nullptr,
                               const TagRow& tagrow = {});

    template <typename T> T* insertItem(SessionItem* parent = nullptr, const TagRow& tagrow = {});

    void removeItem(SessionItem* parent, const TagRow& tagrow);

    void moveItem(SessionItem* item, SessionItem* new_parent, const TagRow& tagrow);

    SessionItem* copyItem(const SessionItem* item, SessionItem* parent, const TagRow& tagrow = {});

    Variant data(SessionItem* item, int role) const;

    bool setData(SessionItem* item, const Variant& value, int role);

    // Various getters.

    std::string modelType() const;

    SessionItem* rootItem() const;

    ModelMapper* mapper();

    UndoStackInterface* undoStack() const;

    const ItemFactoryInterface* factory() const;

    SessionItem* findItem(const identifier_type& id);

    template <typename T = SessionItem> std::vector<T*> topItems() const;

    template <typename T = SessionItem> T* topItem() const;

    // Methods to steer global behaviour.

    void setItemCatalogue(std::unique_ptr<ItemCatalogue> catalogue);

    void setUndoRedoEnabled(bool value);

    void clear(std::function<void(SessionItem*)> callback = {});

    template <typename T> void registerItem(const std::string& label = {});

private:
    friend class SessionItem;
    void registerInPool(SessionItem* item);
    void unregisterFromPool(SessionItem* item);
    SessionItem* intern_insert(const item_factory_func_t& func, SessionItem* parent,
                               const TagRow& tagrow);
    void intern_register(const model_type& modelType, const item_factory_func_t& func,
                         const std::string& label);

    struct SessionModelImpl;
    std::unique_ptr<SessionModelImpl> p_impl;
};

//! Inserts item into given parent under given tagrow.

template <typename T> T* SessionModel::insertItem(SessionItem* parent, const TagRow& tagrow)
{
    return static_cast<T*>(intern_insert(ItemFactoryFunction<T>(), parent, tagrow));
}

//! Returns top items of the given type.
//! The top item is an item that is a child of an invisible root item.

template <typename T> std::vector<T*> SessionModel::topItems() const
{
    std::vector<T*> result;
    for (auto child : rootItem()->children()) {
        if (auto item = dynamic_cast<T*>(child))
            result.push_back(item);
    }

    return result;
}

//! Returns top item of the given type. If more than one item exists, return the first one.
//! The top item is an item that is a child of an invisible root item.

template <typename T> T* SessionModel::topItem() const
{
    auto items = topItems<T>();
    return items.empty() ? nullptr : items.front();
}

//! Register used defined item to use with the model. It will become possible to undo/redo
//! operations with this item, as well as serialize it to/from JSON.

template <typename T> void SessionModel::registerItem(const std::string& label)
{
    intern_register(T().modelType(), ItemFactoryFunction<T>(), label);
}

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONMODEL_H
