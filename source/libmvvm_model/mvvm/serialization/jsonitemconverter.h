// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCONVERTER_H
#define MVVM_SERIALIZATION_JSONITEMCONVERTER_H

#include "mvvm/serialization/jsonitemconverterinterface.h"

namespace ModelView {

struct ConverterContext;

//! Converter between SessionItem and JSON object.

class MVVM_MODEL_EXPORT JsonItemConverter : public JsonItemConverterInterface {
public:
    JsonItemConverter(const ConverterContext& context);
    JsonItemConverter(const JsonItemConverter&) = delete;
    JsonItemConverter& operator=(const JsonItemConverter&) = delete;

    ~JsonItemConverter() override;

    QJsonObject to_json(const SessionItem* item) const override;

    std::unique_ptr<SessionItem> from_json(const QJsonObject& json) const override;

private:
    struct JsonItemConverterImpl;
    std::unique_ptr<JsonItemConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONVERTER_H
