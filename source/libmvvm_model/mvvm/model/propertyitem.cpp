// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/propertyitem.h"
#include "mvvm/model/mvvm_types.h"

using namespace ModelView;

PropertyItem::PropertyItem() : SessionItem(Constants::PropertyType) {}

PropertyItem* PropertyItem::setDisplayName(const std::string& name)
{
    SessionItem::setDisplayName(name);
    return this;
}

PropertyItem* PropertyItem::setLimits(const RealLimits& value)
{
    this->setData(value, ItemDataRole::LIMITS);
    return this;
}
