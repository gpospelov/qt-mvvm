// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/signals/itemmapper.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/modelmapper.h>

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
//!
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
(multilayer*, T_LAYER, row) as callback parameters.
*/

void ItemMapper::setOnRowInserted(Callbacks::item_str_int_t f, Callbacks::slot_t owner)
{
    m_on_row_inserted.connect(std::move(f), owner);
}

/*!
@brief Sets callback to be notified when row is about to be removed.

Callback will be called with (compound_item, tag, row). For MultiLayer containing the T_LAYERS
tag, the signal will be triggered on layer deletion with
(multilayer*, T_LAYER, row) as callback parameters.
*/

void ItemMapper::setOnRowAboutToBeRemoved(Callbacks::item_str_int_t f, Callbacks::slot_t owner)
{
    m_on_row_about_removed.connect(std::move(f), owner);
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
    m_on_row_inserted.remove_client(client);
    m_on_row_about_removed.remove_client(client);
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

    // child property changed
    if (nestling == 2) {
        if(auto parent = item->parent())
            callOnChildPropertyChange(parent, parent->tagFromItem(item));
    }
}

void ItemMapper::onModelRowInserted(SessionItem* parent, std::string tag, int row)
{
    if (parent == m_item)
        callOnRowInserted(m_item, tag, row);
}

void ItemMapper::onModelRowAboutToBeRemoved(SessionItem* parent, std::string tag, int row)
{
    if (parent == m_item)
        callOnRowAboutToBeRemoved(m_item, tag, row);
}

//! Subscribes to model signals.

void ItemMapper::subscribe_to_model()
{
    auto on_data_change = [this](ModelView::SessionItem* item, int role) {onModelDataChange(item, role);};
    m_model->mapper()->setOnDataChange(on_data_change, this);

    auto on_row_inserted = [this](ModelView::SessionItem* item, std::string tag, int row) {
        onModelRowInserted(item, tag, row);
    };
    m_model->mapper()->setOnRowInserted(on_row_inserted, this);

    auto on_row_about_removed = [this](ModelView::SessionItem* item, std::string tag, int row) {
        onModelRowAboutToBeRemoved(item, tag, row);
    };
    m_model->mapper()->setOnRowAboutToBeRemoved(on_row_about_removed, this);
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

void ItemMapper::callOnRowInserted(SessionItem* parent, std::string tag, int row)
{
    if (m_active)
        m_on_row_inserted(parent, tag, row);
}

//! Notifies all callbacks subscribed to "on row about to be removed".

void ItemMapper::callOnRowAboutToBeRemoved(SessionItem* parent, std::string tag, int row)
{
    if (m_active)
        m_on_row_about_removed(parent, tag, row);
}

