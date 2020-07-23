// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/callbackcontainer.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/signals/modelmapper.h>
#include <stdexcept>

using namespace ModelView;

struct ItemMapper::ItemMapperImpl {
    ItemMapper* m_itemMapper{nullptr};
    Signal<Callbacks::item_t> m_on_item_destroy;
    Signal<Callbacks::item_int_t> m_on_data_change;
    Signal<Callbacks::item_str_t> m_on_property_change;
    Signal<Callbacks::item_str_t> m_on_child_property_change;
    Signal<Callbacks::item_tagrow_t> m_on_item_inserted;
    Signal<Callbacks::item_tagrow_t> m_on_item_removed;
    Signal<Callbacks::item_tagrow_t> m_on_about_to_remove_item;

    bool m_active{true};
    SessionItem* m_item{nullptr};

    ItemMapperImpl(ItemMapper* item_mapper) : m_itemMapper(item_mapper) {}

    void unsubscribe(Callbacks::slot_t client)
    {
        m_on_item_destroy.remove_client(client);
        m_on_data_change.remove_client(client);
        m_on_property_change.remove_client(client);
        m_on_child_property_change.remove_client(client);
        m_on_item_inserted.remove_client(client);
        m_on_item_removed.remove_client(client);
        m_on_about_to_remove_item.remove_client(client);
    }

    int nestlingDepth(SessionItem* item, int level = 0)
    {
        if (item == nullptr || item == m_itemMapper->model()->rootItem())
            return -1;
        if (item == m_item)
            return level;
        return nestlingDepth(item->parent(), level + 1);
    }

    //! Processes signals from the model when item data changed.

    void processDataChange(SessionItem* item, int role)
    {
        int nestling = nestlingDepth(item);

        // own item data changed
        if (nestling == 0)
            callOnDataChange(item, role);

        // data of item's property changed
        if (nestling == 1)
            callOnPropertyChange(m_item, m_item->tagOfItem(item));

        // child property changed
        if (nestling == 2) {
            if (auto parent = item->parent())
                callOnChildPropertyChange(parent, parent->tagOfItem(item));
        }
    }

    void processItemInserted(SessionItem* parent, TagRow tagrow)
    {
        if (parent == m_item)
            callOnItemInserted(m_item, tagrow);
    }

    void processItemRemoved(SessionItem* parent, TagRow tagrow)
    {
        if (parent == m_item)
            callOnItemRemoved(m_item, tagrow);
    }

    void processAboutToRemoveItem(SessionItem* parent, TagRow tagrow)
    {
        if (parent == m_item)
            callOnAboutToRemoveItem(m_item, tagrow);
    }

    //! Notifies all callbacks subscribed to "item data is changed" event.

    void callOnDataChange(SessionItem* item, int role)
    {
        if (m_active)
            m_on_data_change(item, role);
    }

    //! Notifies all callbacks subscribed to "item property is changed" event.

    void callOnPropertyChange(SessionItem* item, std::string property_name)
    {
        if (m_active)
            m_on_property_change(item, property_name);
    }

    //! Notifies all callbacks subscribed to "child property changed" event.

    void callOnChildPropertyChange(SessionItem* item, std::string property_name)
    {
        if (m_active)
            m_on_child_property_change(item, property_name);
    }

    //! Notifies all callbacks subscribed to "on row inserted" event.

    void callOnItemInserted(SessionItem* parent, TagRow tagrow)
    {
        if (m_active)
            m_on_item_inserted(parent, tagrow);
    }

    //! Notifies all callbacks subscribed to "on row removed" event.

    void callOnItemRemoved(SessionItem* parent, TagRow tagrow)
    {
        if (m_active)
            m_on_item_removed(parent, tagrow);
    }

    //! Notifies all callbacks subscribed to "on row about to be removed".

    void callOnAboutToRemoveItem(SessionItem* parent, TagRow tagrow)
    {
        if (m_active)
            m_on_about_to_remove_item(parent, tagrow);
    }
};

ItemMapper::ItemMapper(SessionItem* item)
    : ModelListener(item->model()), p_impl(std::make_unique<ItemMapperImpl>(this))
{
    if (!item)
        throw std::runtime_error("ItemMapper::ItemMapper() -> Not initialized item");

    if (!item->model())
        throw std::runtime_error("ItemMapper::ItemMapper() -> Item doesn't have model");

    p_impl->m_item = item;

    auto on_data_change = [this](auto item, auto role) { p_impl->processDataChange(item, role); };
    ModelListener::setOnDataChange(on_data_change);

    auto on_item_inserted = [this](auto item, auto tagrow) {
        p_impl->processItemInserted(item, tagrow);
    };
    ModelListener::setOnItemInserted(on_item_inserted, this);

    auto on_item_removed = [this](auto item, auto tagrow) {
        p_impl->processItemRemoved(item, tagrow);
    };
    ModelListener::setOnItemRemoved(on_item_removed, this);

    auto on_about_to_remove_item = [this](auto item, auto tagrow) {
        p_impl->processAboutToRemoveItem(item, tagrow);
    };
    ModelListener::setOnAboutToRemoveItem(on_about_to_remove_item, this);
}

ItemMapper::~ItemMapper() = default;

void ItemMapper::setOnItemDestroy(Callbacks::item_t f, Callbacks::slot_t owner)
{
    p_impl->m_on_item_destroy.connect(std::move(f), owner);
}

void ItemMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t owner)
{
    p_impl->m_on_data_change.connect(std::move(f), owner);
}

void ItemMapper::setOnPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner)
{
    p_impl->m_on_property_change.connect(std::move(f), owner);
}

void ItemMapper::setOnChildPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner)
{
    p_impl->m_on_child_property_change.connect(std::move(f), owner);
}

void ItemMapper::setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    p_impl->m_on_item_inserted.connect(std::move(f), owner);
}

void ItemMapper::setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    p_impl->m_on_item_removed.connect(std::move(f), owner);
}

void ItemMapper::setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    p_impl->m_on_about_to_remove_item.connect(std::move(f), owner);
}

void ItemMapper::unsubscribe(Callbacks::slot_t client)
{
    p_impl->unsubscribe(client);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void ItemMapper::setActive(bool value)
{
    p_impl->m_active = value;
}

//! Calls all callbacks subscribed to "item is destroyed" event.

void ItemMapper::callOnItemDestroy()
{
    if (p_impl->m_active)
        p_impl->m_on_item_destroy(p_impl->m_item);
}
