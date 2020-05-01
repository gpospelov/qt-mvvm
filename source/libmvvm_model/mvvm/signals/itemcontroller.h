// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_ITEMCONTROLLER_H
#define MVVM_SIGNALS_ITEMCONTROLLER_H

#include <mvvm/signals/itemlistenerbase.h>
#include <mvvm/signals/itemmapper.h>

namespace ModelView
{

class SessionItem;

//! Base class for all controllers to track time of life of SessionItem and provide

template <typename T> class ItemController : public ItemListenerBase
{
public:
    T* currentItem() const { return static_cast<T*>(item()); }
};

} // namespace ModelView

#endif // MVVM_SIGNALS_ITEMCONTROLLER_H
