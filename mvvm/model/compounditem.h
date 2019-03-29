// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COMPOUNDITEM_H
#define COMPOUNDITEM_H

#include "propertyitem.h"
#include "sessionitem.h"
#include "taginfo.h"

namespace ModelView
{

//! Complex item holding mixed SessionItem types (single properties and other CompountItems).

class CORE_EXPORT CompoundItem : public SessionItem
{
public:
    CompoundItem(const std::string& modelType = Constants::CompoundType);

    //! Registers single property item.
    template <typename T>
    T* addProperty(const std::string& name, const QVariant& variant = QVariant());

    std::string displayName() const override;

    // tag specifics
    QVariant getItemValue(const std::string& tag) const;

    void setItemValue(const std::string& tag, const QVariant& variant);
};

template <typename T> T* CompoundItem::addProperty(const std::string& name, const QVariant& variant)
{
    T* property = new T;

    registerTag(TagInfo::propertyTag(name, property->modelType()));

    property->setDisplayName(name);
    if (variant.isValid())
        property->setData(variant, ItemDataRole::DATA);

    insertItem(property, name, 0);

    return property;
}

} // namespace ModelView

#endif // COMPOUNDITEM_H
