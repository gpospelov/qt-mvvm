// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef OBSOLETEITEMMAPPER_H
#define OBSOLETEITEMMAPPER_H

#include "callbackcontainer.h"

namespace ModelView
{

class SessionItem;

//! Provides notifications on various SessionItem changes.

class CORE_EXPORT ObsoleteItemMapper
{
    friend class SessionItem;
public:
    ObsoleteItemMapper(SessionItem* item);

    void setOnItemDestroy(Callbacks::item_t f, Callbacks::client_t client = {});
    void setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client = {});

    void setActive(bool value);

    void unsubscribe(Callbacks::client_t client);

private:

    void callOnItemDestroy();
    void callOnDataChange(int role);

    CallbackContainer<Callbacks::item_t> m_on_item_destroy;
    CallbackContainer<Callbacks::item_int_t> m_on_data_change;

    bool m_active;
    SessionItem* m_item;
};

} //

#endif // OBSOLETEITEMMAPPER_H
