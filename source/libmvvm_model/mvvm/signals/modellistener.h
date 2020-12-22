// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_MODELLISTENER_H
#define MVVM_SIGNALS_MODELLISTENER_H

#include "mvvm/signals/modellistenerbase.h"

namespace ModelView {

class SessionItem;

//! Templated class for all objects willing to listen for changes in concrete SessionModel.

template <typename T> class ModelListener : public ModelListenerBase {
public:
    ModelListener(T* session_model) : ModelListenerBase(session_model) {}

    T* model() const { return static_cast<T*>(m_model); }
};

} // namespace ModelView

#endif // MVVM_SIGNALS_MODELLISTENER_H
