// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_MODELMAPPER_H
#define MVVM_SIGNALS_MODELMAPPER_H

#include <mvvm/signals/callbackcontainer.h>
#include <mvvm/model/tagrow.h>

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

    void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t owner);
    void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t owner);
    void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner);
    void setOnItemAboutToBeRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner);
    void setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t owner);
    void setOnModelReset(Callbacks::model_t f, Callbacks::slot_t owner);

    void setActive(bool value);

    void unsubscribe(Callbacks::slot_t client);

private:
    friend class SessionModel;
    friend class SessionItem;

    void callOnDataChange(SessionItem* item, int role);
    void callOnItemInserted(SessionItem* parent, TagRow tagrow);
    void callOnItemRemoved(SessionItem* parent, TagRow tagrow);
    void callOnItemAboutToBeRemoved(SessionItem* parent, TagRow tagrow);
    void callOnModelDestroyed();
    void callOnModelReset();

    Signal<Callbacks::item_int_t> m_on_data_change;
    Signal<Callbacks::item_tagrow_t> m_on_item_inserted;
    Signal<Callbacks::item_tagrow_t> m_on_item_removed;
    Signal<Callbacks::item_tagrow_t> m_on_item_about_removed;
    Signal<Callbacks::model_t> m_on_model_destroyed;
    Signal<Callbacks::model_t> m_on_model_reset;

    bool m_active;
    SessionModel* m_model;
};

} // namespace ModelView

#endif  // MVVM_SIGNALS_MODELMAPPER_H
