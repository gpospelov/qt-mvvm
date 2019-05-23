// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CUSTOMVARIANTS_H
#define MVVM_CUSTOMVARIANTS_H

//! @file customvariants.h
//! Registrations and translations for custom variants.

#include "mvvm_global.h"
#include "reallimits.h"
#include <QMetaType>
#include <QVariant>
#include <string>
#include <vector>

namespace ModelView
{
namespace Utils
{

//! Returns name of variant.
CORE_EXPORT std::string VariantName(const QVariant& variant);

//! Returns type of variant (additionally checks for user type).
CORE_EXPORT int VariantType(const QVariant& variant);

//! Returns true if variants has compatible types.
CORE_EXPORT bool CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue);

//! Returns true if given variants have same type and value.
CORE_EXPORT bool IsTheSame(const QVariant& var1, const QVariant& var2);

//! Converts custom variant to standard variant which Qt views will understand.
CORE_EXPORT QVariant toQtVariant(const QVariant& custom);

//! Converts Qt variant to custom variant on board of SessionItem.
CORE_EXPORT QVariant toCustomVariant(const QVariant& standard);

//! Returns true in the case of double value based variant.
CORE_EXPORT bool IsBoolVariant(const QVariant& variant);

//! Returns true in the case of double value based variant.
CORE_EXPORT bool IsIntVariant(const QVariant& variant);

//! Returns true in the case of double value based variant.
CORE_EXPORT bool IsDoubleVariant(const QVariant& variant);

//! Returns true in the case of double value based variant.
CORE_EXPORT bool IsComboVariant(const QVariant& variant);

//! Returns true in the case of double value based variant.
CORE_EXPORT bool IsStdStringVariant(const QVariant& variant);

//! Returns true in the case of variant based on std::vector<double>.
CORE_EXPORT bool IsDoubleVectorVariant(const QVariant& variant);

//! Returns true in the case of QColor based variant.
CORE_EXPORT bool IsColorVariant(const QVariant& variant);

//! Returns true in the case of ExternalProperty based variant.
CORE_EXPORT bool IsExtPropertyVariant(const QVariant& variant);

//! Returns true in the case of RealLimits based variant.
CORE_EXPORT bool IsRealLimitsVariant(const QVariant& variant);

} // namespace Utils
} // namespace ModelView

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<double>)
Q_DECLARE_METATYPE(ModelView::RealLimits)

#endif // MVVM_CUSTOMVARIANTS_H
