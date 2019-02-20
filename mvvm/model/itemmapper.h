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
public:
    ItemMapper(SessionItem* item);
    ~ItemMapper();

    void setOnDataChange(Callbacks::item_int_t f, Callbacks::client_t client = {});

private:
    void onModelDataChange(SessionItem* item, int role);
    void subscribe_to_model();
    void unsubscribe_from_model();

    void callOnDataChange(SessionItem* item, int role);

    CallbackContainer<Callbacks::item_int_t> m_on_data_change;

    bool m_active;
    SessionItem* m_item;
    SessionModel* m_model;
};

} // ModelView

#endif // IETMMAPPER_H
