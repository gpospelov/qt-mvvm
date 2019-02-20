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

private:
    std::vector<std::pair<T, U>> m_callbacks;
};

template<typename T, typename U>
void CallbackBaseContainer<T, U>::add(T callback, U caller)
{
    m_callbacks.push_back(std::make_pair(callback, caller));
}

template<typename T, typename U>
template<typename... Args>
void CallbackBaseContainer<T, U>::notify(Args&&... args)
{
    for (auto f : m_callbacks)
        f.first(std::forward<Args>(args)...);
}

//! Callback container for specific caller type.

template<typename T>
class CallbackContainer : public CallbackBaseContainer<T, Callbacks::caller_t>
{
};


} // ModelView

#endif
