// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MODELMAPPER_H
#define MODELMAPPER_H

#include "callbackcontainer.h"

namespace ModelView
{

class SessionItem;
class SessionModel;

//! Provides notifications on various SessionModel changes.
//!
//! Used to notify QAbstractItemModel to set the bridge with Qt signal and slots.
//! Used to notify ItemMapper about activity in relatives of specific item.

class CORE_EXPORT ModelMapper
{
    friend class SessionModel;
    friend class SessionItem;
public:
    ModelMapper(SessionModel* item);

    void setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client = {});
    void setOnRowInserted(Callbacks::item_int_t f, Callbacks::client_t client = {});
    void setOnRowRemoved(Callbacks::item_int_t f, Callbacks::client_t client = {});

    void setActive(bool value);

    void unsubscribe(Callbacks::client_t client);

private:
    void callOnDataChange(SessionItem* item, int role);
    void callOnRowInserted(SessionItem* parent, int index);
    void callOnRowRemoved(SessionItem* parent, int index);

    CallbackContainer<Callbacks::item_int_t> m_on_data_change;
    CallbackContainer<Callbacks::item_int_t> m_on_row_inserted;
    CallbackContainer<Callbacks::item_int_t> m_on_row_removed;

    bool m_active;
    SessionModel* m_model;
};

} // ModelView

#endif // MODELMAPPER_H
