// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONVARIANTCONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONVARIANTCONVERTERINTERFACE_H

#include "mvvm/core/variant.h"
#include "mvvm/model_export.h"

class QJsonObject;

namespace ModelView {

//! Base class for all supported converters of Variant to/from json object

class MVVM_MODEL_EXPORT JsonVariantConverterInterface {
public:
    virtual ~JsonVariantConverterInterface() = default;

    virtual QJsonObject get_json(const Variant&) = 0;

    virtual Variant get_variant(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONVARIANTCONVERTERINTERFACE_H
