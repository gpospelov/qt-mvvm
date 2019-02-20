// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef CALLBACKCONTAINER_H
#define CALLBACKCONTAINER_H

#include "global.h"
#include "model_types.h"
#include <vector>
#include <algorithm>

namespace ModelView
{

class SessionItem;
class SessionModel;

//! Container to hold callbacks in the context of ModelMapper.

template<typename T, typename U>
class CallbackBaseContainer
{
public:
    CallbackBaseContainer() = default;

    void add(T callback, U caller);

    template <typename... Args> void notify(Args&&... args);

    void remove_caller(U caller);

private:
    std::vector<std::pair<T, U>> m_callbacks;
};

template<typename T, typename U>
void CallbackBaseContainer<T, U>::add(T callback, U caller)
{
    m_callbacks.push_back(std::make_pair(callback, caller));
}

//! Notify clients using given list of arguments.

template<typename T, typename U>
template<typename... Args>
void CallbackBaseContainer<T, U>::notify(Args&&... args)
{
    for (auto f : m_callbacks)
        f.first(std::forward<Args>(args)...);
}

//! Remove client from the list to call back.

template<typename T, typename U>
void CallbackBaseContainer<T, U>::remove_caller(U caller)
{
    m_callbacks.erase(std::remove_if(m_callbacks.begin(), m_callbacks.end(),
                           [caller](typename std::vector<std::pair<T, U>>::value_type const& x) -> bool {
                               return (x.second == caller ? true : false);
                           }),
            m_callbacks.end());
}

//! Callback container for specific caller type.

template<typename T>
class CallbackContainer : public CallbackBaseContainer<T, Callbacks::caller_t>
{
};


} // ModelView

#endif
