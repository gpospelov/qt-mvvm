// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_ABSTRACTMODELLISTENER_H
#define MVVM_SIGNALS_ABSTRACTMODELLISTENER_H

#include <mvvm/signals/callback_types.h>

namespace ModelView
{

class SessionModel;

//! Abstract class defining interface to subscribe for various changes in a model.
//! Automatically tracks the time of life of SessionModel. Unsubscribes from the model on
//! own destruction.

class AbstractModelListener
{
public:
    AbstractModelListener(SessionModel* model);
    virtual ~AbstractModelListener();

    void setOnDataChange(Callbacks::item_int_t f);
    void setOnItemInserted(Callbacks::item_tagrow_t f);
    void setOnItemRemoved(Callbacks::item_tagrow_t f);
    void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f);
    void setOnModelReset(Callbacks::model_t f);

protected:
    SessionModel* m_model{nullptr};
};

} // namespace ModelView

#endif // MVVM_SIGNALS_MODELLISTENER_H
