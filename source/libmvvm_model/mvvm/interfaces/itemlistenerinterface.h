// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_ITEMLISTENERINTERFACE_H
#define MVVM_INTERFACES_ITEMLISTENERINTERFACE_H

#include "mvvm/signals/callback_types.h"

namespace ModelView {

//! Interface to subscribe to various events happening with specific SessionItem.

class MVVM_MODEL_EXPORT ItemListenerInterface {
public:
    virtual ~ItemListenerInterface() = default;

    virtual void setOnItemDestroy(Callbacks::item_t f, Callbacks::slot_t owner) = 0;

    //! Sets callback to be notified on item's data change.
    //! Callback will be called with (SessionItem*, data_role).

    virtual void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t owner) = 0;

    //! Sets callback to be notified on item's property change.
    //! Callback will be called with (compound_item, property_name).

    virtual void setOnPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner) = 0;

    //! Sets callback to be notified on item's children property change.
    //! Callback will be called with (compound_item, property_name). For MultiLayer containing the
    //! layer with "thickness" property, the signal will be triggered on thickness change using
    //! (layeritem*, "thickness") as callback parameters.

    virtual void setOnChildPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner) = 0;

    //! Sets callback to be notified on child insertion.
    //! Callback will be called with (compound_item, tag, row). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer insertion with
    //! (multilayer*, {T_LAYER, row}) as callback parameters.

    virtual void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) = 0;

    //! Sets callback to be notified on child removal.
    //! Callback will be called with (compound_item, tag, row). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer removal with
    //! (multilayer*, {T_LAYER, oldrow}) as callback parameters.

    virtual void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) = 0;

    //! Sets callback to be notified when row is about to be removed.
    //! Callback will be called with (compound_item, tagrow). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer deletion with
    //! (multilayer*, {T_LAYER, row}) as callback parameters.

    virtual void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) = 0;

    //! Removes given client from all subscriptions.
    virtual void unsubscribe(Callbacks::slot_t client) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ITEMLISTENERINTERFACE_H
