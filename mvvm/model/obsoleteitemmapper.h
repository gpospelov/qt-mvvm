// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef OBSOLETEITEMMAPPER_H
#define OBSOLETEITEMMAPPER_H

#include "global.h"
#include "model_types.h"
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace ModelView
{

class SessionItem;

//! Provides notifications on various SessionItem changes.

class CORE_EXPORT ObsoleteItemMapper
{
    friend class SessionItem;
public:
    ObsoleteItemMapper(SessionItem* item);

    void setOnItemDestroy(Callbacks::item_t f, Callbacks::caller_t caller = 0);
    void setOnDataChange(Callbacks::item_int_t f, Callbacks::caller_t caller = 0);

    void setActive(bool value);

    void unsubscribe(Callbacks::caller_t caller);

private:
    template <class U> void clean_container(U& v, Callbacks::caller_t caller);

    void callOnItemDestroy();
    void callOnDataChange(int role);

    std::vector<std::pair<Callbacks::item_t, Callbacks::caller_t>> m_on_item_destroy;
    std::vector<std::pair<Callbacks::item_int_t, Callbacks::caller_t>> m_on_data_change;

    bool m_active;
    SessionItem* m_item;
};

template <class U> inline void ObsoleteItemMapper::clean_container(U& v, const void* caller)
{
    v.erase(std::remove_if(v.begin(), v.end(),
                           [caller](typename U::value_type const& x) -> bool {
                               return (x.second == caller ? true : false);
                           }),
            v.end());
}

} //

#endif // OBSOLETEITEMMAPPER_H
