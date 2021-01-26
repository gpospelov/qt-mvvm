// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/signals/modelmapper.h"
#include "mvvm/signals/callbackcontainer.h"

using namespace ModelView;

struct ModelMapper::ModelMapperImpl {
    Signal<Callbacks::item_int_t> m_on_data_change;
    Signal<Callbacks::item_tagrow_t> m_on_item_inserted;
    Signal<Callbacks::item_tagrow_t> m_on_item_removed;
    Signal<Callbacks::item_tagrow_t> m_on_item_about_removed;
    Signal<Callbacks::model_t> m_on_model_destroyed;
    Signal<Callbacks::model_t> m_on_model_about_reset;
    Signal<Callbacks::model_t> m_on_model_reset;

    bool m_active{true};
    SessionModel* m_model{nullptr};

    ModelMapperImpl(SessionModel* model) : m_model(model){};

    void unsubscribe(Callbacks::slot_t client)
    {
        m_on_data_change.remove_client(client);
        m_on_item_inserted.remove_client(client);
        m_on_item_removed.remove_client(client);
        m_on_item_about_removed.remove_client(client);
        m_on_model_destroyed.remove_client(client);
        m_on_model_about_reset.remove_client(client);
        m_on_model_reset.remove_client(client);
    }
};

ModelMapper::ModelMapper(SessionModel* model) : p_impl(std::make_unique<ModelMapperImpl>(model)) {}

ModelMapper::~ModelMapper() = default;

//! Sets callback to be notified on item's data change. The callback will be called
//! with (SessionItem*, data_role).

void ModelMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t client)
{
    p_impl->m_on_data_change.connect(std::move(f), client);
}

//! Sets callback to be notified on item insert. The callback will be called with
//! (SessionItem* parent, tagrow), where 'tagrow' denotes inserted child position.

void ModelMapper::setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t client)
{
    p_impl->m_on_item_inserted.connect(std::move(f), client);
}

//! Sets callback to be notified on item remove. The callback will be called with
//! (SessionItem* parent, tagrow), where 'tagrow' denotes child position before the removal.

void ModelMapper::setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t client)
{
    p_impl->m_on_item_removed.connect(std::move(f), client);
}

//! Sets callback to be notified when the item is about to be removed. The callback will be called
//! with (SessionItem* parent, tagrow), where 'tagrow' denotes child position being removed.

void ModelMapper::setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t client)
{
    p_impl->m_on_item_about_removed.connect(std::move(f), client);
}

//! Sets the callback for notifications on model destruction.

void ModelMapper::setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t client)
{
    p_impl->m_on_model_destroyed.connect(std::move(f), client);
}

//! Sets the callback to be notified just before the reset of the root item.

void ModelMapper::setOnModelAboutToBeReset(Callbacks::model_t f, Callbacks::slot_t client)
{
    p_impl->m_on_model_about_reset.connect(std::move(f), client);
}

//! Sets the callback to be notified right after the root item recreation.

void ModelMapper::setOnModelReset(Callbacks::model_t f, Callbacks::slot_t client)
{
    p_impl->m_on_model_reset.connect(std::move(f), client);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void ModelMapper::setActive(bool value)
{
    p_impl->m_active = value;
}

//! Removes given client from all subscriptions.

void ModelMapper::unsubscribe(Callbacks::slot_t client)
{
    p_impl->unsubscribe(client);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void ModelMapper::callOnDataChange(SessionItem* item, int role)
{
    if (p_impl->m_active)
        p_impl->m_on_data_change(item, role);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void ModelMapper::callOnItemInserted(SessionItem* parent, const TagRow& tagrow)
{
    if (p_impl->m_active)
        p_impl->m_on_item_inserted(parent, tagrow);
}

void ModelMapper::callOnItemRemoved(SessionItem* parent, const TagRow& tagrow)
{
    if (p_impl->m_active)
        p_impl->m_on_item_removed(parent, tagrow);
}

void ModelMapper::callOnItemAboutToBeRemoved(SessionItem* parent, const TagRow& tagrow)
{
    if (p_impl->m_active)
        p_impl->m_on_item_about_removed(parent, tagrow);
}

void ModelMapper::callOnModelDestroyed()
{
    p_impl->m_on_model_destroyed(p_impl->m_model);
}

void ModelMapper::callOnModelAboutToBeReset()
{
    p_impl->m_on_model_about_reset(p_impl->m_model);
}

void ModelMapper::callOnModelReset()
{
    p_impl->m_on_model_reset(p_impl->m_model);
}
