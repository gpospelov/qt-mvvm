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

#include <QString>
#include <mvvm/serialization/jsonconverterinterfaces.h>

class QJsonObject;

namespace ModelView
{

class SessionModel;

class CORE_EXPORT JsonModelConverter : public JsonModelConverterInterface
{
public:
    static const QString modelKey;
    static const QString itemsKey;
    static const QString versionKey;

    JsonModelConverter();
    ~JsonModelConverter() override;

    //! Writes content of model into json.
    void model_to_json(const SessionModel& model, QJsonObject& json) const override;

    //! Reads json object and build the model.
    void json_to_model(const QJsonObject& json, SessionModel& model) const override;

    //! Returns true if given json object represents SessionModel.
    bool isSessionModel(const QJsonObject& object) const;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONMODELCONVERTER_H
