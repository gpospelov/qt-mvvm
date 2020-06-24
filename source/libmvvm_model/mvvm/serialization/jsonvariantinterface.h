// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONVARIANTINTERFACE_H
#define MVVM_SERIALIZATION_JSONVARIANTINTERFACE_H

#include <mvvm/model_export.h>

class QJsonObject;
class QVariant;

namespace ModelView
{

//! Base class for all supported converters of QVariant to/from json object

class MVVM_MODEL_EXPORT JsonVariantInterface
{
public:
    virtual ~JsonVariantInterface() = default;

    virtual QJsonObject get_json(const QVariant&) = 0;

    virtual QVariant get_variant(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONVARIANTINTERFACE_H
