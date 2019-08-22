// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemcontroller.h"
#include "itemmapper.h"
#include "sessionitem.h"

using namespace ModelView;

struct ItemController::ItemControllerPrivate {
    SessionItem* m_item{nullptr};
};

ItemController::ItemController(QObject* parent)
    : QObject(parent), p_impl(std::make_unique<ItemControllerPrivate>())
{
}

void ItemController::setItem(SessionItem* item)
{
    if (p_impl->m_item == item)
        return;

    if (p_impl->m_item) {
        p_impl->m_item->mapper()->unsubscribe(this);
    }

    p_impl->m_item = item;
    if (!p_impl->m_item)
        return;

    auto on_item_destroy = [this](SessionItem*) { p_impl->m_item = nullptr; };
    p_impl->m_item->mapper()->setOnItemDestroy(on_item_destroy, this);

    subscribe();
}

SessionItem* ItemController::currentItem() const
{
    return p_impl->m_item;
}

void ItemController::subscribe() {}

ItemController::~ItemController()
{
    if (p_impl->m_item)
        p_impl->m_item->mapper()->unsubscribe(this);
}
