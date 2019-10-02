// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"

using namespace ModelView;

ModelMapper::ModelMapper(SessionModel* item) : m_active(true), m_model(item) {}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (SessionItem*, data_role).

void ModelMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client)
{
    m_on_data_change.add(std::move(f), client);
}

//! Sets callback to be notified on item insert.
//! Callback will be called with (SessionItem* parent, tag, row), where tag,row corresponds
//! to inserted child.

void ModelMapper::setOnRowInserted(Callbacks::item_str_int_t f, Callbacks::client_t client)
{
    m_on_row_inserted.add(std::move(f), client);
}

//! Sets callback to be notified on removed row.
//! Callback will be called with (SessionItem* parent, tag, row), where tag,row corresponds
//! to removed child.

void ModelMapper::setOnRowRemoved(Callbacks::item_str_int_t f, Callbacks::client_t client)
{
    m_on_row_removed.add(std::move(f), client);
}

//! Sets callback to be notified when row is about to be removed.
//! Callback will be called with (SessionItem* parent, tag, row), where tag,row corresponds
//! to the child which going to be removed.

void ModelMapper::setOnRowAboutToBeRemoved(Callbacks::item_str_int_t f, Callbacks::client_t client)
{
    m_on_row_about_removed.add(std::move(f), client);
}

//! Sets the callback for notifications on model destruction.

void ModelMapper::setOnModelDestroyed(Callbacks::model_t f, Callbacks::client_t client)
{
    m_on_model_destroyed.add(std::move(f), client);
}

void ModelMapper::setOnModelReset(Callbacks::model_t f, Callbacks::client_t client)
{
    m_on_model_reset.add(std::move(f), client);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void ModelMapper::setActive(bool value)
{
    m_active = value;
}

//! Removes given client from all subscriptions.

void ModelMapper::unsubscribe(Callbacks::client_t client)
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

void ModelMapper::callOnRowInserted(SessionItem* parent, std::string tag, int row)
{
    if (m_active)
        m_on_row_inserted(parent, tag, row);
}

void ModelMapper::callOnRowRemoved(SessionItem* parent, std::string tag, int row)
{
    if (m_active)
        m_on_row_removed(parent, tag, row);
}

void ModelMapper::callOnRowAboutToBeRemoved(SessionItem* parent, std::string tag, int row)
{
    if (m_active)
        m_on_row_about_removed(parent, tag, row);
}

void ModelMapper::callOnModelDestroyed()
{
    m_on_model_destroyed(m_model);
}

void ModelMapper::callOnModelReset()
{
    m_on_model_reset(m_model);
}
