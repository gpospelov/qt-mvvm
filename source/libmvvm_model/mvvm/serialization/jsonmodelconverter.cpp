// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/serialization/jsonmodelconverter.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/serialization/jsonitemconverter.h>
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>

using namespace ModelView;

namespace {
QStringList expected_model_keys() {
    QStringList result = QStringList() << JsonModelConverter::modelKey << JsonModelConverter::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}


}

const QString ModelView::JsonModelConverter::modelKey = "model";
const QString ModelView::JsonModelConverter::itemsKey = "items";
const QString ModelView::JsonModelConverter::versionKey = "version";


JsonModelConverter::JsonModelConverter() = default;

JsonModelConverter::~JsonModelConverter() = default;

void JsonModelConverter::model_to_json(const SessionModel& model, QJsonObject& json) const
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::to_json() -> Error. Model is not initialized.");

    json[modelKey] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

    auto converter = std::make_unique<JsonItemConverter>(model.factory());

    for(auto item : model.rootItem()->children())
        itemArray.append(converter->to_json(item));

    json[itemsKey] = itemArray;
}

void JsonModelConverter::json_to_model(const QJsonObject& json, SessionModel& model) const
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Model is not initialized.");

    if (model.rootItem()->childrenCount())
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Model is not empty.");

    if (!isSessionModel(json))
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Invalid json object.");

    if (json[modelKey].toString() != QString::fromStdString(model.modelType()))
            throw std::runtime_error("JsonModel::json_to_model() -> Unexpected model type.");

    auto converter = std::make_unique<JsonItemConverter>(model.factory());

    auto parent = model.rootItem();
    for(const auto ref : json[itemsKey].toArray()) {
        auto item =converter->from_json(ref.toObject());
        parent->insertItem(item.release(), TagRow::append());
    }
}

bool JsonModelConverter::isSessionModel(const QJsonObject& object) const
{
    static const QStringList expected = expected_model_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}

