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

ModelMapper::ModelMapper(SessionModel* item)
    : m_active(true), m_model(item)
{

}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (SessionItem*, data_role).

void ModelMapper::setOnDataChange(Callbacks::item_int_t f, Callbacks::caller_t caller)
{
    m_on_data_change.push_back(std::make_pair(f, caller));
}

//! Sets callback to be notified on item insert.
//! Callback will be called with (SessionItem* parent, index), where index correspondx
//! to new item index in children array.

void ModelMapper::setOnRowInserted(Callbacks::item_int_t f, Callbacks::caller_t caller)
{
    m_on_row_inserted.push_back(std::make_pair(f, caller));
}

//! Sets callback to be notified on removed row.
//! Callback will be called with (SessionItem* parent, index), where index correspondx
//! to removed index in children array.

void ModelMapper::setOnRowRemoved(Callbacks::item_int_t f, Callbacks::caller_t caller)
{
    m_on_row_removed.push_back(std::make_pair(f, caller));
}

void ModelMapper::setOnRowRemoved2(Callbacks::item_int_str_t f, Callbacks::caller_t caller)
{
    m_on_row_removed2.push_back(std::make_pair(f, caller));
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void ModelMapper::setActive(bool value)
{
    m_active = value;
}

//! Removes given caller from all subscriptions.

void ModelMapper::unsubscribe(Callbacks::caller_t caller)
{
    clean_container(m_on_data_change, caller);
}

//! Calls all callbacks subscribed to "item data is changed" event.

void ModelMapper::callOnDataChange(SessionItem* item, int role)
{
    if (m_active)
        for (auto f : m_on_data_change)
            f.first(item, role);
}

//! Calls all callbacks subscribed to "item data is changed" event.

void ModelMapper::callOnRowInserted(SessionItem* parent, int index)
{
    if (m_active)
        for (auto f : m_on_row_inserted)
            f.first(parent, index);
}

void ModelMapper::callOnRowRemoved(SessionItem* parent, int index)
{
    if (m_active)
        for (auto f : m_on_row_removed)
            f.first(parent, index);
}

void ModelMapper::callOnRowRemoved2(SessionItem* parent, int index, std::string id)
{
    if (m_active)
        for (auto f : m_on_row_removed2)
            f.first(parent, index, id);
}
