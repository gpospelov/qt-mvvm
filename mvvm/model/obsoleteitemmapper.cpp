// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "obsoleteitemmapper.h"

using namespace ModelView;

ObsoleteItemMapper::ObsoleteItemMapper(SessionItem* item)
    : m_active(true), m_item(item)
{

}

void ObsoleteItemMapper::setOnItemDestroy(Callbacks::item_t f, Callbacks::client_t client)
{
    m_on_item_destroy.add(f, client);
}

void ObsoleteItemMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client)
{
    m_on_data_change.add(f, client);
}


//! Sets activity flag to given value. Will disable all callbacks if false.

void ObsoleteItemMapper::setActive(bool value)
{
    m_active = value;
}

//! Removes given client from all subscriptions.

void ObsoleteItemMapper::unsubscribe(Callbacks::client_t client)
{
    m_on_item_destroy.remove_client(client);
    m_on_data_change.remove_client(client);
}

//! Calls all callbacks subscribed to "item is destroyed" event.

void ObsoleteItemMapper::callOnItemDestroy()
{
    if (m_active)
        m_on_item_destroy.notify(m_item);
}

//! Calls all callbacks subscribed to "item data is changed" event.

void ObsoleteItemMapper::callOnDataChange(int role)
{
    if (m_active)
        m_on_data_change.notify(m_item, role);
}
