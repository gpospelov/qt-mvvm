// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_COMPOUNDITEM_H
#define MVVM_MODEL_COMPOUNDITEM_H

#include "mvvm/model/customvariants.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/utils/reallimits.h"

namespace ModelView {

//! Complex item holding mixed SessionItem types (single properties and other CompountItems).

class MVVM_MODEL_EXPORT CompoundItem : public SessionItem {
public:
    CompoundItem(const std::string& modelType = Constants::CompoundItemType);

    //! Adds property item of given type and register it under the given 'name'.
    template <typename T = PropertyItem> T* addProperty(const std::string& name);

    //! Adds PropertyItem and sets its value to 'value'.
    template <typename V> PropertyItem* addProperty(const std::string& name, const V& value);

    //! Register char property. Special case to turn it into std::string.
    PropertyItem* addProperty(const std::string& name, const char* value);

    std::string displayName() const override;
};

template <typename T> T* CompoundItem::addProperty(const std::string& name)
{
    registerTag(TagInfo::propertyTag(name, T().modelType()));
    auto result = insertItem<T>({name, 0});
    result->setDisplayName(name);
    return result;
}

inline PropertyItem* CompoundItem::addProperty(const std::string& name, const char* value)
{
    // Consider merging with the method ::addProperty(const std::string& name, const V& value).
    // Currently it is not possible because of QVariant dependency. It converts 'const char*'
    // to QString, and we want std::string.
    return addProperty(name, std::string(value));
}

template <typename V>
PropertyItem* CompoundItem::addProperty(const std::string& name, const V& value)
{
    auto property = addProperty<PropertyItem>(name);
    property->setData(value);
    if constexpr (std::is_floating_point_v<V>)
        property->setData(RealLimits::limitless(), ItemDataRole::LIMITS);
    return property;
}

} // namespace ModelView

#endif // MVVM_MODEL_COMPOUNDITEM_H
