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

#include <mvvm/serialization/jsonmodelconverterinterface.h>
class QJsonObject;

namespace ModelView
{

class SessionModel;

//! Default converter of SessionModel to/from json object.
//! `COPY_MODE` is used to make a full copy of given model, `PROJECT_MODE` is used
//! for selective saving of model on disk.

class MVVM_MODEL_EXPORT JsonModelConverter : public JsonModelConverterInterface
{
public:
    enum class ConverterMode {COPY_MODE, PROJECT_MODE};
    JsonModelConverter(ConverterMode mode = ConverterMode::COPY_MODE);
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
