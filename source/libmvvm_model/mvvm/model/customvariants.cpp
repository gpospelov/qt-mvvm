// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/customvariants.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/variant_constants.h"

namespace {
const QString qstring_name = "QString";
}

using namespace ModelView;

std::string Utils::VariantName(const Variant& variant)
{
    return variant.isValid() ? variant.typeName() : Constants::invalid_type_name;
}

int Utils::VariantType(const Variant& variant)
{
    auto result = static_cast<int>(variant.type());
    if (result == Variant::UserType)
        result = variant.userType();
    return result;
}

bool Utils::CompatibleVariantTypes(const Variant& oldValue, const Variant& newValue)
{
    // Invalid variant can be rewritten by any variant.
    // Valid Variant can be replaced by invalid variant.
    // In other cases types of variants should coincide to be compatible.

    if (!oldValue.isValid() || !newValue.isValid())
        return true;

    return Utils::VariantType(oldValue) == Utils::VariantType(newValue);
}

bool Utils::IsTheSame(const Variant& var1, const Variant& var2)
{
    // variants of different type are always reported as not the same
    if (VariantType(var1) != VariantType(var2))
        return false;

    // variants of same type are compared by value
    return var1 == var2;
}

Variant Utils::toQtVariant(const Variant& custom)
{
    if (!custom.isValid())
        return custom;

    // converts variant based on std::string to variant based on QString
    if (custom.typeName() == Constants::string_type_name) {
        return Variant(QString::fromStdString(custom.value<std::string>()));
    }
    else if (IsDoubleVectorVariant(custom)) {
        QString str =
            QString("vector of %1 elements").arg(custom.value<std::vector<double>>().size());
        return Variant(str);
    }

    // in other cases returns unchanged variant
    return custom;
}

Variant Utils::toCustomVariant(const Variant& standard)
{
    if (!standard.isValid())
        return standard;

    // converts variant based on std::string to variant based on QString
    if (standard.typeName() == qstring_name)
        return Variant::fromValue(standard.toString().toStdString());

    // in other cases returns unchanged variant
    return standard;
}

bool Utils::IsBoolVariant(const Variant& variant)
{
    return variant.type() == Variant::Bool;
}

bool Utils::IsIntVariant(const Variant& variant)
{
    return variant.type() == Variant::Int;
}

bool Utils::IsDoubleVariant(const Variant& variant)
{
    return variant.type() == Variant::Double;
}

bool Utils::IsComboVariant(const Variant& variant)
{
    return variant.canConvert<ComboProperty>();
}

bool Utils::IsStdStringVariant(const Variant& variant)
{
    return variant.canConvert<std::string>();
}

bool Utils::IsDoubleVectorVariant(const Variant& variant)
{
    return variant.typeName() == Constants::vector_double_type_name;
}

bool Utils::IsColorVariant(const Variant& variant)
{
    return variant.type() == Variant::Color;
}

bool Utils::IsExtPropertyVariant(const Variant& variant)
{
    return variant.canConvert<ExternalProperty>();
}

bool Utils::IsRealLimitsVariant(const Variant& variant)
{
    return variant.canConvert<RealLimits>();
}
