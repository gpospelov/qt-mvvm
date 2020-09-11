// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonArray>
#include <QJsonObject>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/serialization/jsonitemconverter_v2.h>
#include <mvvm/serialization/jsonitemformatassistant.h>
#include <mvvm/serialization/jsonmodelconverter.h>
#include <stdexcept>

using namespace ModelView;

JsonModelConverter::JsonModelConverter() = default;

JsonModelConverter::~JsonModelConverter() = default;

void JsonModelConverter::model_to_json(const SessionModel& model, QJsonObject& json) const
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::to_json() -> Error. Model is not initialized.");

    json[JsonItemFormatAssistant::sessionModelKey] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

    auto converter = std::make_unique<JsonItemConverterV2>(model.factory());

    for (auto item : model.rootItem()->children())
        itemArray.append(converter->to_json(item));

    json[JsonItemFormatAssistant::itemsKey] = itemArray;
}

void JsonModelConverter::json_to_model(const QJsonObject& json, SessionModel& model) const
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Model is not initialized.");

    JsonItemFormatAssistant assistant;
    if (!assistant.isSessionModel(json))
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Invalid json object.");

    if (json[JsonItemFormatAssistant::sessionModelKey].toString()
        != QString::fromStdString(model.modelType()))
        throw std::runtime_error(
            "JsonModel::json_to_model() -> Unexpected model type '" + model.modelType()
            + "', json key '"
            + json[JsonItemFormatAssistant::sessionModelKey].toString().toStdString() + "'");

    auto converter = std::make_unique<JsonItemConverterV2>(model.factory());

    auto rebuild_root = [&json, &converter](auto parent) {
        for (const auto ref : json[JsonItemFormatAssistant::itemsKey].toArray()) {
            auto item = converter->from_json(ref.toObject());
            parent->insertItem(item.release(), TagRow::append());
        }
    };
    model.clear(rebuild_root);
}
