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
#include "sessionitem.h"
#include "taginfo.h"
#include "reallimits.h"

namespace ModelView
{

//! Complex item holding mixed SessionItem types (single properties and other CompountItems).

class CORE_EXPORT CompoundItem : public SessionItem
{
public:
    CompoundItem(const std::string& modelType = Constants::CompoundType);

    //! Registers single property item.
    template <typename T = PropertyItem>
    T* addProperty(const std::string& name, const QVariant& variant = QVariant());

    //! Register char property as variant based on std::string.
    template <typename T = PropertyItem> T* addProperty(const std::string& name, const char* str);

    std::string displayName() const override;
};

template <typename T> T* CompoundItem::addProperty(const std::string& name, const QVariant& variant)
{
    T* property = new T;

    registerTag(TagInfo::propertyTag(name, property->modelType()));

    property->setDisplayName(name);
    if (variant.isValid())
        property->setData(variant);

    if (variant.type() == QVariant::Double)
        property->setData(QVariant::fromValue<RealLimits>(RealLimits::positive()), ItemDataRole::LIMITS);

    insertItem(property, {name, 0});

    return property;
}

template <typename T> T* CompoundItem::addProperty(const std::string& name, const char* str)
{
    return addProperty<T>(name, QVariant::fromValue(std::string(str)));
}

} // namespace ModelView

#endif // MVVM_COMPOUNDITEM_H
