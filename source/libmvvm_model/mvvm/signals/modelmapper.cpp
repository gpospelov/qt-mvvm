// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/signals/modelmapper.h>

using namespace ModelView;

ModelMapper::ModelMapper(SessionModel* item) : m_active(true), m_model(item) {}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (SessionItem*, data_role).

void ModelMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t owner)
{
    m_on_data_change.connect(std::move(f), owner);
}

//! Sets callback to be notified on item insert.
//! Callback will be called with (SessionItem* parent, tag, row), where tag,row corresponds
//! to inserted child.

void ModelMapper::setOnRowInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    m_on_row_inserted.connect(std::move(f), owner);
}

//! Sets callback to be notified on removed row.
//! Callback will be called with (SessionItem* parent, tag, row), where tag,row corresponds
//! to removed child.

void ModelMapper::setOnRowRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    m_on_row_removed.connect(std::move(f), owner);
}

//! Sets callback to be notified when row is about to be removed.
//! Callback will be called with (SessionItem* parent, tag, row), where tag,row corresponds
//! to the child which going to be removed.

void ModelMapper::setOnRowAboutToBeRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    m_on_row_about_removed.connect(std::move(f), owner);
}

//! Sets the callback for notifications on model destruction.

void ModelMapper::setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t owner)
{
    m_on_model_destroyed.connect(std::move(f), owner);
}

void ModelMapper::setOnModelReset(Callbacks::model_t f, Callbacks::slot_t owner)
{
    m_on_model_reset.connect(std::move(f), owner);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void ModelMapper::setActive(bool value)
{
    m_active = value;
}

//! Removes given client from all subscriptions.

void ModelMapper::unsubscribe(Callbacks::slot_t client)
{
    m_on_data_change.remove_client(client);
    m_on_row_inserted.remove_client(client);
    m_on_row_removed.remove_client(client);
    m_on_row_about_removed.remove_client(client);
    m_on_model_destroyed.remove_client(client);
    m_on_model_reset.remove_client(client);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void ModelMapper::callOnDataChange(SessionItem* item, int role)
{
    if (m_active)
        m_on_data_change(item, role);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void ModelMapper::callOnRowInserted(SessionItem* parent, TagRow tagrow)
{
    if (m_active)
        m_on_row_inserted(parent, tagrow);
}

void ModelMapper::callOnRowRemoved(SessionItem* parent, TagRow tagrow)
{
    if (m_active)
        m_on_row_removed(parent, tagrow);
}

void ModelMapper::callOnRowAboutToBeRemoved(SessionItem* parent, TagRow tagrow)
{
    if (m_active)
        m_on_row_about_removed(parent, tagrow);
}

void ModelMapper::callOnModelDestroyed()
{
    m_on_model_destroyed(m_model);
}

void ModelMapper::callOnModelReset()
{
    m_on_model_reset(m_model);
}
