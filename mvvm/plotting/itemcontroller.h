// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMCONTROLLER_H
#define MVVM_ITEMCONTROLLER_H

#include "itemmapper.h"
#include "mvvm_export.h"
#include <memory>

namespace ModelView
{

class SessionItem;

/*!
@class ItemController
@brief Controller to track time of life of SessionItem.
*/

template <typename T> class ItemControllerV2
{
public:
    virtual ~ItemControllerV2() {
        if (m_item)
            m_item->mapper()->unsubscribe(this);
    }

    void setItem(T* item)
    {
        if (m_item == item)
            return;

        if (m_item)
            m_item->mapper()->unsubscribe(this);

        m_item = item;

        if (!m_item)
            return;

        auto on_item_destroy = [this](SessionItem*) { m_item = nullptr; };
        m_item->mapper()->setOnItemDestroy(on_item_destroy, this);

        subscribe();
    }

    T* currentItem() const { return m_item; }

protected:
    virtual void subscribe() {}

private:
    T* m_item{nullptr};
};

} // namespace ModelView

#endif // MVVM_ITEMCONTROLLER_H
