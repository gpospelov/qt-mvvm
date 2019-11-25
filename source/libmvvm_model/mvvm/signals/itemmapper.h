// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_ITEMMAPPER_H
#define MVVM_SIGNALS_ITEMMAPPER_H

#include <mvvm/signals/callbackcontainer.h>

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

    void setModel(SessionModel* model);

    void setOnItemDestroy(Callbacks::item_t f, Callbacks::slot_t owner);
    void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t owner);
    void setOnPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner);
    void setOnChildPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner);
    void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t owner);
    void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t owner);

    void setActive(bool value);

    void unsubscribe(Callbacks::slot_t client);

private:
    void processDataChange(SessionItem* item, int role);
    void processItemInserted(SessionItem* parent, TagRow tagrow);
    void processAboutToRemoveItem(SessionItem* parent, TagRow tagrow);
    void subscribe_to_model();
    void unsubscribe_from_model();
    int nestlingDepth(SessionItem* item, int level = 0);

    void callOnItemDestroy();
    void callOnDataChange(SessionItem* item, int role);
    void callOnPropertyChange(SessionItem* item, std::string property_name);
    void callOnChildPropertyChange(SessionItem* item, std::string property_name);
    void callOnItemInserted(SessionItem* parent, TagRow tagrow);
    void callOnAboutToRemoveItem(SessionItem* parent, TagRow tagrow);

    Signal<Callbacks::item_t> m_on_item_destroy;
    Signal<Callbacks::item_int_t> m_on_data_change;
    Signal<Callbacks::item_str_t> m_on_property_change;
    Signal<Callbacks::item_str_t> m_on_child_property_change;
    Signal<Callbacks::item_tagrow_t> m_on_item_inserted;
    Signal<Callbacks::item_tagrow_t> m_on_about_to_remove_item;

    bool m_active;
    SessionItem* m_item;
    SessionModel* m_model;
};

} // ModelView

#endif  // MVVM_SIGNALS_ITEMMAPPER_H
