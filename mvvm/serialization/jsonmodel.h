// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONMODEL_H
#define JSONMODEL_H

#include "jsonconverterinterfaces.h"
#include <QString>
#include <memory>

class QJsonObject;

namespace ModelView {

class SessionModel;
class SessionItem;
class JsonItemInterface;

class CORE_EXPORT JsonModel : public JsonModelInterface
{
public:
    static const QString modelKey;
    static const QString itemDataKey;
    static const QString itemsKey;
    static const QString versionKey;

    JsonModel();
    ~JsonModel() override;

    //! Writes content of model into json.
    void model_to_json(const SessionModel& model, QJsonObject& json) const override;

    //! Reads json object and build the model.
    void json_to_model(const QJsonObject& json, SessionModel& model) const override;

    //! Constructs SessionItem tree from json.
    void json_to_item(const QJsonObject& json, SessionItem* parent, int row = -1) const override;

    //! Writes SessionItem tree to json.
    void item_to_json(const SessionItem* item, QJsonObject& json) const override;

    //! Returns true if given json object represents SessionItem tree.
    bool is_item(const QJsonObject& object) const;

    //! Returns true if given json object represents SessionModel.
    bool is_model(const QJsonObject& object) const;

private:
    std::unique_ptr<JsonItemInterface> m_item_converter;
};

}  // namespace ModelView

#endif // JSONMODEL_H

