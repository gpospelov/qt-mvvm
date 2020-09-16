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

namespace
{
const QVariant empty_link = QVariant::fromValue(std::string());
}

LinkedItem::LinkedItem() : SessionItem(Constants::LinkedItemType)
{
    setData(empty_link);
    setEditable(false); // prevent editing in widgets, link is set programmatically.
}

//! Set link to given item.

void LinkedItem::setLink(const SessionItem* item)
{
    setData(item ? QVariant::fromValue(item->identifier()) : empty_link);
}
