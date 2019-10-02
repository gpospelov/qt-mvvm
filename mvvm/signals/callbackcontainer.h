// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CALLBACKCONTAINER_H
#define MVVM_CALLBACKCONTAINER_H

#include "mvvm_export.h"
#include "callback_types.h"
#include <algorithm>
#include <functional>
#include <vector>

namespace ModelView
{

class SessionItem;
class SessionModel;

//! Container to hold callbacks in the context of ModelMapper.

template <typename T, typename U> class CallbackBaseContainer
{
public:
    CallbackBaseContainer() = default;

    void connect(T callback, U client);

    template <typename... Args> void operator()(Args... args);

    void remove_client(U client);

private:
    std::vector<std::pair<T, U>> m_callbacks;
};

template <typename T, typename U> void CallbackBaseContainer<T, U>::connect(T callback, U client)
{
    m_callbacks.push_back(std::make_pair(callback, client));
}


//! Notify clients using given list of arguments.
template <typename T, typename U>
template <typename... Args>
void CallbackBaseContainer<T, U>::operator()(Args... args)
{
    for (const auto& f : m_callbacks) {
        f.first(args...);
    }
}

//! Remove client from the list to call back.

template <typename T, typename U> void CallbackBaseContainer<T, U>::remove_client(U client)
{
    m_callbacks.erase(std::remove_if(m_callbacks.begin(), m_callbacks.end(),
                                     [client](const std::pair<T, U>& x) -> bool {
                                         return (x.second == client ? true : false);
                                     }),
                      m_callbacks.end());
}

//! Callback container for specific client type.

template <typename T> class CallbackContainer : public CallbackBaseContainer<T, Callbacks::client_t>
{
};

} // ModelView

#endif // MVVM_CALLBACKCONTAINER_H
