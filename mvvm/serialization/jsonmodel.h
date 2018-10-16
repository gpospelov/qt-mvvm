// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //


#ifndef MODELJSON_H
#define MODELJSON_H

#include "jsonconverterinterfaces.h"
#include <QString>
#include <memory>

class SessionModel;
class QJsonObject;
class SessionItem;
class JsonItemDataInterface;

class JsonModel : public JsonModelInterface
{
public:
    static const QString modelKey;
    static const QString itemDataKey;
    static const QString itemsKey;
    static const QString versionKey;

    JsonModel();

    //! Writes content of model into json.
    void model_to_json(const SessionModel& model, QJsonObject& json);

    //! Reads json object and build the model.
    void json_to_model(const QJsonObject& json, SessionModel& model);

    //! Constructs SessionItem tree from json.
    void json_to_item(const QJsonObject& json, SessionItem* parent, int row = -1);

    //! Writes SessionItem tree to json.
    void item_to_json(const SessionItem* item, QJsonObject& json);

    //! Returns true if given json object represents SessionItem tree.
    bool is_item(const QJsonObject& object);

    //! Returns true if given json object represents SessionModel.
    bool is_model(const QJsonObject& object);

private:
    std::unique_ptr<JsonItemDataInterface> m_itemdata_converter;
};

#endif
