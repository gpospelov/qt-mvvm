// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/customvariants.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/propertyitem.h>

using namespace ModelView;

PropertyItem::PropertyItem() : SessionItem(Constants::PropertyType) {}

SessionItem* PropertyItem::setLimits(const RealLimits& value)
{
    this->setData(QVariant::fromValue<RealLimits>(value), ItemDataRole::LIMITS);
    return this;
}
