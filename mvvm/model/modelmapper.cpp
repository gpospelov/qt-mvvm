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

void ModelMapper::setOnDataChange(ModelMapper::func_item_int_t f, ModelMapper::caller_t caller)
{
    m_on_data_change.push_back(std::make_pair(f, caller));
}

//! Sets callback to be notified on item insert.
//! Callback will be called with (SessionItem* parent, index).

void ModelMapper::setOnRowInserted(ModelMapper::func_item_int_t f, ModelMapper::caller_t caller)
{
    m_on_row_inserted.push_back(std::make_pair(f, caller));
}


//! Sets activity flag to given value. Will disable all callbacks if false.

void ModelMapper::setActive(bool value)
{
    m_active = value;
}

//! Removes given caller from all subscriptions.

void ModelMapper::unsubscribe(ModelMapper::caller_t caller)
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

void ModelMapper::callOnRowInserted(SessionItem* item, int index)
{
    if (m_active)
        for (auto f : m_on_row_inserted)
            f.first(item, index);
}
