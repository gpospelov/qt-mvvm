// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef IETMMAPPER_H
#define IETMMAPPER_H

#include "callbackcontainer.h"

namespace ModelView
{

class SessionItem;
class SessionModel;

//! Provides notifications on varios changes for specific item.
//!
//! ItemMapper listens signals coming from the model (i.e. via ModelMapper) and processes only whose
//! signals which are related to given item. Notifies all interested subscribers about things
//! going with given item and its relatives.

class CORE_EXPORT ItemMapper
{
    friend class SessionItem;
public:
    ItemMapper(SessionItem* item);
    ~ItemMapper();

    void setOnItemDestroy(Callbacks::item_t f, Callbacks::client_t client = {});
    void setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client = {});
    void setOnPropertyChange(Callbacks::item_str_t f, Callbacks::client_t client = {});

    void setActive(bool value);

    void unsubscribe(Callbacks::client_t client);

private:
    void onModelDataChange(SessionItem* item, int role);
    void subscribe_to_model();
    void unsubscribe_from_model();

    void callOnItemDestroy();
    void callOnDataChange(SessionItem* item, int role);
    void callOnPropertyChange(SessionItem* item, std::string property_name);

    CallbackContainer<Callbacks::item_t> m_on_item_destroy;
    CallbackContainer<Callbacks::item_int_t> m_on_data_change;
    CallbackContainer<Callbacks::item_str_t> m_on_property_change;

    bool m_active;
    SessionItem* m_item;
    SessionModel* m_model;
};

} // ModelView

#endif // IETMMAPPER_H
