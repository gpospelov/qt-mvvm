// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_MODELMAPPER_H
#define MVVM_MODELMAPPER_H

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
public:
    ModelMapper(SessionModel* item);

    void setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client = {});
    void setOnRowInserted(Callbacks::item_str_int_t f, Callbacks::client_t client = {});
    void setOnRowRemoved(Callbacks::item_str_int_t f, Callbacks::client_t client = {});
    void setOnRowAboutToBeRemoved(Callbacks::item_str_int_t f, Callbacks::client_t client = {});
    void setOnModelDestroyed(Callbacks::model_t f, Callbacks::client_t client = {});
    void setOnModelReset(Callbacks::model_t f, Callbacks::client_t client = {});

    void setActive(bool value);

    void unsubscribe(Callbacks::client_t client);

private:
    friend class SessionModel;
    friend class SessionItem;

    void callOnDataChange(SessionItem* item, int role);
    void callOnRowInserted(SessionItem* parent, std::string tag, int row);
    void callOnRowRemoved(SessionItem* parent, std::string tag, int row);
    void callOnRowAboutToBeRemoved(SessionItem* parent, std::string tag, int row);
    void callOnModelDestroyed();
    void callOnModelReset();

    CallbackContainer<Callbacks::item_int_t> m_on_data_change;
    CallbackContainer<Callbacks::item_str_int_t> m_on_row_inserted;
    CallbackContainer<Callbacks::item_str_int_t> m_on_row_removed;
    CallbackContainer<Callbacks::item_str_int_t> m_on_row_about_removed;
    CallbackContainer<Callbacks::model_t> m_on_model_destroyed;
    CallbackContainer<Callbacks::model_t> m_on_model_reset;

    bool m_active;
    SessionModel* m_model;
};

} // namespace ModelView

#endif // MVVM_MODELMAPPER_H
