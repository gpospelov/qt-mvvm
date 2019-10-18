// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "linkeditem.h"
#include "customvariants.h"

using namespace ModelView;

LinkedItem::LinkedItem() : SessionItem(Constants::LinkedType) {}

//! Set link to given item.

void LinkedItem::setLink(const SessionItem* item)
{
    setData(item ? QVariant::fromValue(item->identifier()) : QVariant());
}
