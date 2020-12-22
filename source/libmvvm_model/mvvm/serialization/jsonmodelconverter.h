// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONMODELCONVERTER_H
#define MVVM_SERIALIZATION_JSONMODELCONVERTER_H

#include "mvvm/serialization/jsonmodelconverterinterface.h"

class QJsonObject;

namespace ModelView {

class SessionModel;
enum class ConverterMode;

//! Converter of SessionModel to/from json object with posibility to select one of convertion modes.

class MVVM_MODEL_EXPORT JsonModelConverter : public JsonModelConverterInterface {
public:
    JsonModelConverter(ConverterMode mode);
    ~JsonModelConverter() override;

    //! Writes content of model into json.
    QJsonObject to_json(const SessionModel& model) const override;

    //! Reads json object and build the model.
    void from_json(const QJsonObject& json, SessionModel& model) const override;

private:
    ConverterMode m_mode;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONMODELCONVERTER_H
