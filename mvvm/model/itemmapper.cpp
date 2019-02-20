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

    // FIXME consider m_model removal. But what to do then, when item changes the model?
    m_model = m_item->model();

    subscribe_to_model();
}

ItemMapper::~ItemMapper()
{
    unsubscribe_from_model();
}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (SessionItem*, data_role).

void ItemMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client)
{
    m_on_data_change.add(f, client);
}

//! Processes signals from the model when item data changed.

void ItemMapper::onModelDataChange(SessionItem* item, int role)
{
    if (item == m_item)
        callOnDataChange(item, role);
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

//! Notifies all callbacks subscribed to "item data is changed" event.

void ItemMapper::callOnDataChange(SessionItem* item, int role)
{
    if (m_active)
        m_on_data_change.notify(item, role);
}
