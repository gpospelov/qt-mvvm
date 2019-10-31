// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COMPOUNDITEM_H
#define MVVM_COMPOUNDITEM_H

#include "customvariants.h"
#include "propertyitem.h"
#include "reallimits.h"
#include "sessionitem.h"
#include "taginfo.h"
#include <type_traits>

namespace ModelView
{

//! Complex item holding mixed SessionItem types (single properties and other CompountItems).

class CORE_EXPORT CompoundItem : public SessionItem
{
public:
    CompoundItem(const std::string& modelType = Constants::CompoundItemType);

    //! Adds property item of given type.
    template <typename T = PropertyItem> T* addProperty(const std::string& name);

    template <typename T = PropertyItem, typename V>
    T* addProperty(const std::string& name, const V& value);

    //! Register char property. Special case to turn it into std::string.
    template <typename T = PropertyItem> T* addProperty(const std::string& name, const char* value);

    std::string displayName() const override;
};

template <typename T> T* CompoundItem::addProperty(const std::string& name)
{
    T* property = new T;
    registerTag(TagInfo::propertyTag(name, property->modelType()));
    property->setDisplayName(name);
    insertItem(property, {name, 0});
    return property;
}

template <typename T> T* CompoundItem::addProperty(const std::string& name, const char* value)
{
    return addProperty<T>(name, std::string(value));
}

template <typename T, typename V>
T* CompoundItem::addProperty(const std::string& name, const V& value)
{
    T* property = new T;
    registerTag(TagInfo::propertyTag(name, property->modelType()));
    property->setDisplayName(name);
    property->setData(QVariant::fromValue(value));

    if constexpr (std::is_floating_point_v<V>)
        property->setData(QVariant::fromValue<RealLimits>(RealLimits::positive()),
                          ItemDataRole::LIMITS);

    insertItem(property, {name, 0});
    return property;
}

} // namespace ModelView

#endif // MVVM_COMPOUNDITEM_H
