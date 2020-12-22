// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_CALLBACKCONTAINER_H
#define MVVM_SIGNALS_CALLBACKCONTAINER_H

#include "mvvm/model_export.h"
#include "mvvm/signals/callback_types.h"
#include <algorithm>
#include <functional>
#include <list>

namespace ModelView {

class SessionItem;
class SessionModel;

//! Container to hold callbacks in the context of ModelMapper.

template <typename T, typename U> class SignalBase {
public:
    SignalBase() = default;

    void connect(T callback, U client);

    template <typename... Args> void operator()(Args... args);

    void remove_client(U client);

private:
    std::list<std::pair<T, U>> m_callbacks;
};

template <typename T, typename U> void SignalBase<T, U>::connect(T callback, U client)
{
    m_callbacks.push_back(std::make_pair(callback, client));
}

//! Notify clients using given list of arguments.
template <typename T, typename U>
template <typename... Args>
void SignalBase<T, U>::operator()(Args... args)
{
    for (const auto& f : m_callbacks) {
        f.first(args...);
    }
}

//! Remove client from the list to call back.

template <typename T, typename U> void SignalBase<T, U>::remove_client(U client)
{
    m_callbacks.remove_if(
        [client](const std::pair<T, U>& x) -> bool { return (x.second == client ? true : false); });
}

//! Callback container for specific client type.

template <typename T> class Signal : public SignalBase<T, Callbacks::slot_t> {
};

} // namespace ModelView

#endif // MVVM_SIGNALS_CALLBACKCONTAINER_H
