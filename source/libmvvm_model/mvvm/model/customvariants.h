// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_CUSTOMVARIANTS_H
#define MVVM_MODEL_CUSTOMVARIANTS_H

//! @file customvariants.h
//! Registrations and translations for custom variants.

#include "mvvm/core/variant.h"
#include "mvvm/model_export.h"
#include "mvvm/utils/reallimits.h"
#include <QMetaType>
#include <string>
#include <vector>

namespace ModelView::Utils {

//! Returns name of variant.
MVVM_MODEL_EXPORT std::string VariantName(const Variant& variant);

//! Returns type of variant (additionally checks for user type).
MVVM_MODEL_EXPORT int VariantType(const Variant& variant);

//! Returns true if variants has compatible types.
MVVM_MODEL_EXPORT bool CompatibleVariantTypes(const Variant& oldValue, const Variant& newValue);

//! Returns true if given variants have same type and value.
MVVM_MODEL_EXPORT bool IsTheSame(const Variant& var1, const Variant& var2);

//! Converts custom variant to standard variant which Qt views will understand.
MVVM_MODEL_EXPORT Variant toQtVariant(const Variant& custom);

//! Converts Qt variant to custom variant on board of SessionItem.
MVVM_MODEL_EXPORT Variant toCustomVariant(const Variant& standard);

//! Returns true in the case of double value based variant.
MVVM_MODEL_EXPORT bool IsBoolVariant(const Variant& variant);

//! Returns true in the case of double value based variant.
MVVM_MODEL_EXPORT bool IsIntVariant(const Variant& variant);

//! Returns true in the case of double value based variant.
MVVM_MODEL_EXPORT bool IsDoubleVariant(const Variant& variant);

//! Returns true in the case of double value based variant.
MVVM_MODEL_EXPORT bool IsComboVariant(const Variant& variant);

//! Returns true in the case of double value based variant.
MVVM_MODEL_EXPORT bool IsStdStringVariant(const Variant& variant);

//! Returns true in the case of variant based on std::vector<double>.
MVVM_MODEL_EXPORT bool IsDoubleVectorVariant(const Variant& variant);

//! Returns true in the case of QColor based variant.
MVVM_MODEL_EXPORT bool IsColorVariant(const Variant& variant);

//! Returns true in the case of ExternalProperty based variant.
MVVM_MODEL_EXPORT bool IsExtPropertyVariant(const Variant& variant);

//! Returns true in the case of RealLimits based variant.
MVVM_MODEL_EXPORT bool IsRealLimitsVariant(const Variant& variant);

} // namespace ModelView::Utils

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<double>)
Q_DECLARE_METATYPE(ModelView::RealLimits)

#endif // MVVM_MODEL_CUSTOMVARIANTS_H
