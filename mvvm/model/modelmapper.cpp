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

ModelMapper::ModelMapper(SessionModel* item) : m_active(true), m_model(item)
{
}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (SessionItem*, data_role).

void ModelMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client)
{
    m_on_data_change.add(f, client);
}

//! Sets callback to be notified on item insert.
//! Callback will be called with (SessionItem* parent, index), where index correspondx
//! to new item index in children array.

void ModelMapper::setOnRowInserted(Callbacks::item_str_int_t f, Callbacks::client_t client)
{
    m_on_row_inserted.add(f, client);
}

//! Sets callback to be notified on removed row.
//! Callback will be called with (SessionItem* parent, index), where index correspondx
//! to removed index in children array.

void ModelMapper::setOnRowRemoved(Callbacks::item_str_int_t f, Callbacks::client_t client)
{
    m_on_row_removed.add(f, client);
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
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void ModelMapper::callOnDataChange(SessionItem* item, int role)
{
    if (m_active)
        m_on_data_change.notify(item, role);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void ModelMapper::callOnRowInserted(SessionItem* parent, std::string tag, int index)
{
    if (m_active)
        m_on_row_inserted.notify(parent, tag, index);
}

void ModelMapper::callOnRowRemoved(SessionItem* parent, std::string tag, int index)
{
    if (m_active)
        m_on_row_removed.notify(parent, tag, index);
}
