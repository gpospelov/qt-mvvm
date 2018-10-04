// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemutils.h"
#include "sessionitem.h"

void Utils::iterate(const SessionItem* item, const std::function<void(const SessionItem*)>& fun)
{
    if (item)
        fun(item);
    else
        return;

    for (auto child : item->children())
        iterate(child, fun);
}

void Utils::iterate_if(const SessionItem* item, const std::function<bool(const SessionItem*)>& fun)
{
    bool proceed_with_children(true);

    if (item)
        proceed_with_children = fun(item);

    if (!item || !proceed_with_children)
        return;

    for (auto child : item->children())
        iterate_if(child, fun);
}

int Utils::VariantType(const QVariant& variant)
{
    int result = static_cast<int>(variant.type());
    if (result == QVariant::UserType)
        result = variant.userType();
    return result;
}

bool Utils::CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue)
{
    // if olfValue is undefined than it is compatible with any value, otherwise newValue
    // should have same variant type as oldValue

    if (oldValue.isValid())
        return Utils::VariantType(oldValue) == Utils::VariantType(newValue);
    else
        return true;
}

// For custom variants (based on ExternalProperty, ComboProperty) will always return false, i.e.
// we will rely here on our custom editors.
// This is done to not to register custom comparators in main.cpp.
bool Utils::IsTheSame(const QVariant& var1, const QVariant& var2)
{
    // variants of different type are always reported as not the same
    if (VariantType(var1) != VariantType(var2))
        return false;

    // custom type variants are always reported as not the same
    if (var1.type() == QVariant::UserType)
        return false;

    // standard variants (based on double, int, etc) are compared by value they are holding
    return var1 == var2;
}
