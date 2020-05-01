// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "itemlistenerbase.h"
#include <mvvm/model/sessionitem.h>
#include <mvvm/signals/itemmapper.h>

ModelView::ItemListenerBase::ItemListenerBase(ModelView::SessionItem* item)
{
    setItem(item);
}

ModelView::ItemListenerBase::~ItemListenerBase()
{
    if (m_item)
        m_item->mapper()->unsubscribe(this);
}

void ModelView::ItemListenerBase::setItem(ModelView::SessionItem* item)
{
    if (m_item == item)
        return;

    unsubscribe_from_current();

    m_item = item;

    if (!m_item)
        return;

    auto on_item_destroy = [this](auto) { m_item = nullptr; };
    m_item->mapper()->setOnItemDestroy(on_item_destroy, this);

    subscribe();
}

ModelView::SessionItem* ModelView::ItemListenerBase::item() const
{
    return m_item;
}

void ModelView::ItemListenerBase::unsubscribe_from_current()
{
    if (!m_item)
        return;

    unsubscribe();

    m_item->mapper()->unsubscribe(this);
}
