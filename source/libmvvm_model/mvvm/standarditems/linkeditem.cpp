// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/customvariants.h>
#include <mvvm/standarditems/linkeditem.h>

using namespace ModelView;

LinkedItem::LinkedItem() : SessionItem(Constants::LinkedItemType)
{
    setEditable(false); // prevent editing in widgets, link is set programmatically.
}

//! Set link to given item.

void LinkedItem::setLink(const SessionItem* item)
{
    setData(item ? QVariant::fromValue(item->identifier()) : QVariant());
}
