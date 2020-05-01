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
#include <mvvm/signals/itemmapper.h>
#include <mvvm/signals/modelmapper.h>

using namespace ModelView;

ItemMapper::ItemMapper(SessionItem* item) : m_active(true), m_item(item), m_model(nullptr)
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

void ItemMapper::setOnItemDestroy(Callbacks::item_t f, Callbacks::slot_t owner)
{
    m_on_item_destroy.connect(std::move(f), owner);
}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (SessionItem*, data_role).

void ItemMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t owner)
{
    m_on_data_change.connect(std::move(f), owner);
}

//! Sets callback to be notified on item's property change.
//! Callback will be called with (compound_item, property_name).

void ItemMapper::setOnPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner)
{
    m_on_property_change.connect(std::move(f), owner);
}

/*!
@brief Sets callback to be notified on item's children property change.

Callback will be called with (compound_item, property_name). For MultiLayer containing the
layer with "thickness" property, the signal will be triggered on thickness change using
(layeritem*, "thickness") as callback parameters.
*/

void ItemMapper::setOnChildPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner)
{
    m_on_child_property_change.connect(std::move(f), owner);
}

/*!
@brief Sets callback to be notified on child insertion.

Callback will be called with (compound_item, tag, row). For MultiLayer containing the T_LAYERS
tag, the signal will be triggered on layer insertion with
(multilayer*, {T_LAYER, row}) as callback parameters.
*/

void ItemMapper::setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    m_on_item_inserted.connect(std::move(f), owner);
}

/*!
@brief Sets callback to be notified on child removal.

Callback will be called with (compound_item, tag, row). For MultiLayer containing the T_LAYERS
tag, the signal will be triggered on layer removal with
(multilayer*, {T_LAYER, oldrow}) as callback parameters.
*/

void ItemMapper::setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    m_on_item_removed.connect(std::move(f), owner);
}

/*!
@brief Sets callback to be notified when row is about to be removed.

Callback will be called with (compound_item, tagrow). For MultiLayer containing the T_LAYERS
tag, the signal will be triggered on layer deletion with
(multilayer*, {T_LAYER, row}) as callback parameters.
*/

void ItemMapper::setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t owner)
{
    m_on_about_to_remove_item.connect(std::move(f), owner);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void ItemMapper::setActive(bool value)
{
    m_active = value;
}

void ItemMapper::unsubscribe(Callbacks::slot_t client)
{
    m_on_item_destroy.remove_client(client);
    m_on_data_change.remove_client(client);
    m_on_property_change.remove_client(client);
    m_on_child_property_change.remove_client(client);
    m_on_item_inserted.remove_client(client);
    m_on_item_removed.remove_client(client);
    m_on_about_to_remove_item.remove_client(client);
}

//! Processes signals from the model when item data changed.

void ItemMapper::processDataChange(SessionItem* item, int role)
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

void ItemMapper::processItemInserted(SessionItem* parent, TagRow tagrow)
{
    if (parent == m_item)
        callOnItemInserted(m_item, tagrow);
}

void ItemMapper::processItemRemoved(SessionItem* parent, TagRow tagrow)
{
    if (parent == m_item)
        callOnItemRemoved(m_item, tagrow);
}

void ItemMapper::processAboutToRemoveItem(SessionItem* parent, TagRow tagrow)
{
    if (parent == m_item)
        callOnAboutToRemoveItem(m_item, tagrow);
}

//! Subscribes to model signals.

void ItemMapper::subscribe_to_model()
{
    auto on_data_change = [this](ModelView::SessionItem* item, int role) {
        processDataChange(item, role);
    };
    m_model->mapper()->setOnDataChange(on_data_change, this);

    auto on_item_inserted = [this](ModelView::SessionItem* item, TagRow tagrow) {
        processItemInserted(item, tagrow);
    };
    m_model->mapper()->setOnItemInserted(on_item_inserted, this);

    auto on_item_removed = [this](ModelView::SessionItem* item, TagRow tagrow) {
        processItemRemoved(item, tagrow);
    };
    m_model->mapper()->setOnItemRemoved(on_item_removed, this);

    auto on_about_to_remove_item = [this](ModelView::SessionItem* item, ModelView::TagRow tagrow) {
        processAboutToRemoveItem(item, tagrow);
    };
    m_model->mapper()->setOnAboutToRemoveItem(on_about_to_remove_item, this);
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
        m_on_item_destroy(m_item);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void ItemMapper::callOnDataChange(SessionItem* item, int role)
{
    if (m_active)
        m_on_data_change(item, role);
}

//! Notifies all callbacks subscribed to "item property is changed" event.

void ItemMapper::callOnPropertyChange(SessionItem* item, std::string property_name)
{
    if (m_active)
        m_on_property_change(item, property_name);
}

//! Notifies all callbacks subscribed to "child property changed" event.

void ItemMapper::callOnChildPropertyChange(SessionItem* item, std::string property_name)
{
    if (m_active)
        m_on_child_property_change(item, property_name);
}

//! Notifies all callbacks subscribed to "on row inserted" event.

void ItemMapper::callOnItemInserted(SessionItem* parent, TagRow tagrow)
{
    if (m_active)
        m_on_item_inserted(parent, tagrow);
}

//! Notifies all callbacks subscribed to "on row removed" event.

void ItemMapper::callOnItemRemoved(SessionItem* parent, TagRow tagrow)
{
    if (m_active)
        m_on_item_removed(parent, tagrow);
}

//! Notifies all callbacks subscribed to "on row about to be removed".

void ItemMapper::callOnAboutToRemoveItem(SessionItem* parent, TagRow tagrow)
{
    if (m_active)
        m_on_about_to_remove_item(parent, tagrow);
}
