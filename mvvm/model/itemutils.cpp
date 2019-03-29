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

using namespace ModelView;

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
    auto result = static_cast<int>(variant.type());
    if (result == QVariant::UserType)
        result = variant.userType();
    return result;
}

bool Utils::CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue)
{
    // Invalid variant can be rewritten by any variant.
    // Valid Variant can be replaced by invalid variant.
    // In other cases types of variants should coincide to be compatible.

    if (!oldValue.isValid() || !newValue.isValid())
        return true;

    return Utils::VariantType(oldValue) == Utils::VariantType(newValue);
}

bool Utils::IsTheSame(const QVariant& var1, const QVariant& var2)
{
    // variants of different type are always reported as not the same
    if (VariantType(var1) != VariantType(var2))
        return false;

    // variants of same type are compared by value
    return var1 == var2;
}



int Utils::CopyNumber(const SessionItem* item)
{
    int result(-1);

    if(!item)
        return result;

    int count(0);
    auto model_type = item->modelType();
    if (auto parent = item->parent()) {
        for (auto child : parent->children()) {
            if (child == item)
                result = count;
            if (child->modelType() == model_type)
                ++count;
        }
    }

    return count >1 ? result : -1;
}

SessionItem* Utils::ChildAt(const SessionItem* parent, int index)
{
    if (!parent)
        return nullptr;

    auto container = parent->children();
    return index >= 0 && static_cast<size_t>(index) < container.size()
               ? container[static_cast<size_t>(index)]
               : nullptr;
}
