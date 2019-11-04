// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "propertyitem.h"
#include "mvvm_types.h"
#include "customvariants.h"

using namespace ModelView;

PropertyItem::PropertyItem() : SessionItem(Constants::PropertyType)
{

}

SessionItem& PropertyItem::setLimits(const RealLimits& value)
{
    this->setData( QVariant::fromValue<RealLimits>(value), ItemDataRole::LIMITS);
    return *this;
}
