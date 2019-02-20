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

#include "global.h"
#include "model_types.h"
#include "callbackcontainer.h"
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace ModelView
{

class SessionItem;
class SessionModel;

//! Provides notifications on various SessionModel changes.
//! Used to notify QAbstractItemModel.

class CORE_EXPORT ModelMapper
{
    friend class SessionModel;
    friend class SessionItem;
public:
    ModelMapper(SessionModel* item);

    void setOnDataChange(Callbacks::item_int_t f, Callbacks::caller_t caller = 0);
    void setOnRowInserted(Callbacks::item_int_t f, Callbacks::caller_t caller = 0);
    void setOnRowRemoved(Callbacks::item_int_t f, Callbacks::caller_t caller = 0);
    void setOnRowRemoved2(Callbacks::item_int_str_t f, Callbacks::caller_t caller = 0);

    void setActive(bool value);

    void unsubscribe(Callbacks::caller_t caller);

private:
    void callOnDataChange(SessionItem* item, int role);
    void callOnRowInserted(SessionItem* parent, int index);
    void callOnRowRemoved(SessionItem* parent, int index);
    void callOnRowRemoved2(SessionItem* parent, int index, std::string id);

    CallbackContainer<Callbacks::item_int_t> m_on_data_change;
    CallbackContainer<Callbacks::item_int_t> m_on_row_inserted;
    CallbackContainer<Callbacks::item_int_t> m_on_row_removed;
    CallbackContainer<Callbacks::item_int_str_t> m_on_row_removed2;

    bool m_active;
    SessionModel* m_model;
};

} // ModelView

#endif // MODELMAPPER_H
