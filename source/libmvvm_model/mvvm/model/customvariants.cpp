// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/customvariants.h"
#include "mvvm/core/variant.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/externalproperty.h"
#include <QMetaType>
#include <string>
#include <vector>

Variant ModelView::Utils::toQtVariant(const Variant& custom)
{
    if (!custom.isValid()) return custom;

    // converts variant based on std::string to variant based on QString

    if (custom.userType() == QMetaType::fromType<std::string>().id()) {
        return Variant(QString::fromStdString(custom.value<std::string>()));
    }

    if (IsDoubleVectorVariant(custom)) {
        QString str = QString("vector of %1 elements").arg(custom.value<std::vector<double>>().size());
        return Variant(str);
    }

    // in other cases returns unchanged variant
    return custom;
}

Variant ModelView::Utils::toCustomVariant(const Variant& standard)
{
    if (!standard.isValid()) return standard;

    // converts variant based on std::string to variant based on QString
    if (standard.userType() == QMetaType::fromType<QString>().id()) {
        return Variant::fromValue(standard.toString().toStdString());
    }

    // in other cases returns unchanged variant
    return standard;
}

bool ModelView::Utils::IsBoolVariant(const Variant& variant)
{
    return (variant.userType() == QMetaType::fromType<bool>().id());
}

bool ModelView::Utils::IsIntVariant(const Variant& variant)
{
    return (variant.userType() == QMetaType::fromType<int>().id());
}

bool ModelView::Utils::IsDoubleVariant(const Variant& variant)
{
    return (variant.userType() == QMetaType::fromType<double>().id());
}

bool ModelView::Utils::IsComboVariant(const Variant& variant)
{
    return variant.canConvert<ModelView::ComboProperty>();
}

bool ModelView::Utils::IsStdStringVariant(const Variant& variant)
{
    return variant.canConvert<std::string>();
}

bool ModelView::Utils::IsDoubleVectorVariant(const Variant& variant)
{
    return (variant.userType() == QMetaType::fromType<std::vector<double>>().id());
}

bool ModelView::Utils::IsColorVariant(const Variant& variant)
{
    return (variant.userType() == QMetaType::fromType<QColor>().id());
}

bool ModelView::Utils::IsExtPropertyVariant(const Variant& variant)
{
    return variant.canConvert<ModelView::ExternalProperty>();
}

bool ModelView::Utils::IsRealLimitsVariant(const Variant& variant)
{
    return variant.canConvert<ModelView::RealLimits>();
}
