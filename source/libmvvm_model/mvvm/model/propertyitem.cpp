// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/model/propertyitem.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/customvariants.h>

using namespace ModelView;

PropertyItem::PropertyItem() : SessionItem(Constants::PropertyType)
{

}

SessionItem& PropertyItem::setLimits(const RealLimits& value)
{
    this->setData( QVariant::fromValue<RealLimits>(value), ItemDataRole::LIMITS);
    return *this;
}
