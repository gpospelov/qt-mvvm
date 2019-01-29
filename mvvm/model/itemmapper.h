// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMMAPPER_H
#define ITEMMAPPER_H

#include "global.h"
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace ModelView
{

class SessionItem;

//! Provides notifications on various SessionItem changes.

class CORE_EXPORT ItemMapper
{
    friend class SessionItem;
public:
    using caller_t = const void*;
    using func_item_t = std::function<void(SessionItem*)>;
    using func_item_int_t = std::function<void(SessionItem*, int)>;

    ItemMapper(SessionItem* item);

    void setOnItemDestroy(func_item_t f, caller_t caller = 0);
    void setOnDataChange(func_item_int_t f, caller_t caller = 0);

    void setActive(bool value);

    void unsubscribe(caller_t caller);

private:
    template <class U> void clean_container(U& v, caller_t caller);

    void callOnItemDestroy();
    void callOnDataChange(int role);

    std::vector<std::pair<func_item_t, caller_t>> m_on_item_destroy;
    std::vector<std::pair<func_item_int_t, caller_t>> m_on_data_change;

    bool m_active;
    SessionItem* m_item;
};

template <class U> inline void ItemMapper::clean_container(U& v, const void* caller)
{
    v.erase(std::remove_if(v.begin(), v.end(),
                           [caller](typename U::value_type const& x) -> bool {
                               return (x.second == caller ? true : false);
                           }),
            v.end());
}

} //

#endif // ITEMMAPPER_H
