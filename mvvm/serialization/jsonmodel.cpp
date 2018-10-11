// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonmodel.h"
#include "jsonitemdata.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "itemutils.h"
#include <QSet>
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>

namespace {
QStringList expected_item_keys() {
    QStringList result = QStringList() << JsonModel::modelKey << JsonModel::itemDataKey
                                       << JsonModel::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}

QStringList expected_model_keys() {
    QStringList result = QStringList() << JsonModel::modelKey << JsonModel::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}


}

const QString JsonModel::modelKey = "model";
const QString JsonModel::itemDataKey = "itemData";
const QString JsonModel::itemsKey = "items";
const QString JsonModel::versionKey = "version";


JsonModel::JsonModel()
    : m_itemdata_converter(new JsonItemData)
{

}

void JsonModel::to_json(const SessionModel& model, QJsonObject& json)
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::to_json() -> Error. Model is not initialized.");

    json[modelKey] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

    for(auto item : model.rootItem()->children()) {
        QJsonObject object;
        JsonModel::item_to_json(item, object);
        itemArray.append(object);
    }

    json[itemsKey] = itemArray;
}

void JsonModel::from_json(const QJsonObject& json, SessionModel& model)
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::from_json() -> Error. Model is not initialized.");

    if (model.rootItem()->childrenCount())
        throw std::runtime_error("JsonModel::from_json() -> Error. Model is not empty.");

    if (!is_model(json))
        throw std::runtime_error("JsonModel::from_json() -> Error. Invalid json object.");

    if (json[modelKey].toString() != QString::fromStdString(model.modelType()))
            throw std::runtime_error("JsonModel::from_json() -> Unexpected model type.");

    auto parent = model.rootItem();
//    for(const auto obj : json[itemsKey].toArray()) {
//        json_to_item(obj, parent);

//    }

}

void JsonModel::json_to_item(const QJsonObject& json, SessionItem* parent)
{
    if (!parent)
        throw std::runtime_error("JsonModel::json_to_item() -> Non initialized item");


}

void JsonModel::item_to_json(const SessionItem* item, QJsonObject& json)
{
    if (!item)
        return;

    json[modelKey] = QString::fromStdString(item->modelType());
    json[itemDataKey] = m_itemdata_converter->get_json(item->m_data);

    QJsonArray itemArray;
    for (auto child : item->children()) {
        QJsonObject child_json;
        item_to_json(child, child_json);
        itemArray.append(child_json);
    }
    json[itemsKey] = itemArray;
}

bool JsonModel::is_item(const QJsonObject& object)
{
    static const QStringList expected = expected_item_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    if (!object[itemDataKey].isArray())
        return false;

    return true;
}

bool JsonModel::is_model(const QJsonObject& object)
{
    static const QStringList expected = expected_model_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}

