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

class CORE_EXPORT ItemController
{
public:
    ItemController();
    virtual ~ItemController();

    void setItem(SessionItem* item);

    SessionItem* currentItem() const;

    virtual void subscribe();

private:
    struct ItemControllerPrivate;
    std::unique_ptr<ItemControllerPrivate> p_impl;
};

template <typename T> class ItemControllerV2
{
public:
    virtual ~ItemControllerV2() = default;

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

    virtual void subscribe() {}

private:
    T* m_item{nullptr};
};

} // namespace ModelView

#endif // MVVM_ITEMCONTROLLER_H
