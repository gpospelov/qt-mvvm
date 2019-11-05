// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_JSONMODEL_H
#define MVVM_JSONMODEL_H

#include <mvvm/serialization/jsonconverterinterfaces.h>
#include <QString>

class QJsonObject;

namespace ModelView {

class SessionModel;

class CORE_EXPORT JsonModel : public JsonModelInterface
{
public:
    static const QString modelKey;
    static const QString itemsKey;
    static const QString versionKey;

    JsonModel();
    ~JsonModel() override;

    //! Writes content of model into json.
    void model_to_json(const SessionModel& model, QJsonObject& json) const override;

    //! Reads json object and build the model.
    void json_to_model(const QJsonObject& json, SessionModel& model) const override;

    //! Returns true if given json object represents SessionModel.
    bool isSessionModel(const QJsonObject& object) const;

};

}  // namespace ModelView

#endif // MVVM_JSONMODEL_H

