// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_MODELLISTENERINTERFACE_H
#define MVVM_INTERFACES_MODELLISTENERINTERFACE_H

#include <mvvm/signals/callback_types.h>

namespace ModelView
{

//! Interface to subscribe to various signals generated by SessionModel.

class CORE_EXPORT ModelListenerInterface
{
public:
    virtual ~ModelListenerInterface() = default;

    virtual void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t client) = 0;
    virtual void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t client) = 0;
    virtual void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t client) = 0;
    virtual void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t client) = 0;
    virtual void setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t client) = 0;
    virtual void setOnModelAboutToBeReset(Callbacks::model_t f, Callbacks::slot_t client) = 0;
    virtual void setOnModelReset(Callbacks::model_t f, Callbacks::slot_t client) = 0;
    virtual void unsubscribe(Callbacks::slot_t client) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_MODELLISTENERINTERFACE_H