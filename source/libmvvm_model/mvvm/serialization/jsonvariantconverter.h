// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H
#define MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H

#include "mvvm/core/variant.h"
#include "mvvm/model_export.h"

class QJsonObject;

namespace ModelView {

//! Default converter between supported variants and json objects.

class MVVM_MODEL_EXPORT JsonVariantConverter {
public:
    JsonVariantConverter() = delete;
    static QJsonObject get_json(const Variant& variant);
    static Variant get_variant(const QJsonObject& object);
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H
