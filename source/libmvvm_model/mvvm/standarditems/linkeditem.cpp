// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/standarditems/linkeditem.h>
#include <mvvm/model/customvariants.h>

using namespace ModelView;

LinkedItem::LinkedItem() : SessionItem(Constants::LinkedItemType) {}

//! Set link to given item.

void LinkedItem::setLink(const SessionItem* item)
{
    setData(item ? QVariant::fromValue(item->identifier()) : QVariant());
}
