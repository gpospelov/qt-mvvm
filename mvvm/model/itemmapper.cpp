// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "modelmapper.h"

using namespace ModelView;

ItemMapper::ItemMapper(SessionItem* item)
    : m_active(true), m_item(item), m_model(nullptr)
{
    if (!m_item)
        throw std::runtime_error("ItemMapper::ItemMapper() -> Not initialized item");

    if (!m_item->model())
        throw std::runtime_error("ItemMapper::ItemMapper() -> Item doesn't have model");

    setModel(item->model());
}

ItemMapper::~ItemMapper()
{
    unsubscribe_from_model();
}

void ItemMapper::setModel(SessionModel* model)
{
    if (m_model)
        unsubscribe_from_model();

    m_model = model;

    if (m_model)
        subscribe_to_model();
}

void ItemMapper::setOnItemDestroy(Callbacks::item_t f, Callbacks::client_t client)
{
    m_on_item_destroy.add(f, client);
}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (SessionItem*, data_role).

void ItemMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client)
{
    m_on_data_change.add(f, client);
}

//! Sets callback to be notified on item's property change.
//!
//! Callback will be called with (compound_item, property_name).

void ItemMapper::setOnPropertyChange(Callbacks::item_str_t f, Callbacks::client_t client)
{
    m_on_property_change.add(f, client);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void ItemMapper::setActive(bool value)
{
    m_active = value;
}

void ItemMapper::unsubscribe(Callbacks::client_t client)
{
    m_on_item_destroy.remove_client(client);
    m_on_data_change.remove_client(client);
    m_on_property_change.remove_client(client);
}

//! Processes signals from the model when item data changed.

void ItemMapper::onModelDataChange(SessionItem* item, int role)
{
    int nestling = nestlingDepth(item);

    // own item data changed
    if (nestling == 0)
        callOnDataChange(item, role);

    // data of item's property changed
    if (nestling == 1)
        callOnPropertyChange(m_item, m_item->tagFromItem(item));
}

//! Subscribes to model signals.

void ItemMapper::subscribe_to_model()
{
    m_model->mapper()->setOnDataChange([this](ModelView::SessionItem* item, int role) {
        onModelDataChange(item, role);
    }, this);
}

//! Unsubscribes from model signals.

void ItemMapper::unsubscribe_from_model()
{
    m_model->mapper()->unsubscribe(this);
}

int ItemMapper::nestlingDepth(SessionItem* item, int level)
{
    if (item == nullptr || item == m_model->rootItem())
        return -1;
    if (item == m_item)
        return level;
    return nestlingDepth(item->parent(), level + 1);
}

//! Calls all callbacks subscribed to "item is destroyed" event.

void ItemMapper::callOnItemDestroy()
{
    if (m_active)
        m_on_item_destroy.notify(m_item);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void ItemMapper::callOnDataChange(SessionItem* item, int role)
{
    if (m_active)
        m_on_data_change.notify(item, role);
}

void ItemMapper::callOnPropertyChange(SessionItem* item, std::string property_name)
{
    if (m_active)
        m_on_property_change.notify(item, property_name);
}

