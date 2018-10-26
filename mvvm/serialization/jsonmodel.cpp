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
#include "sessionitemdata.h"
#include "itemutils.h"
#include "itemmanager.h"
#include "customvariants.h"
#include "model_types.h"
#include <QSet>
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>

using namespace ModelView;

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

JsonModel::~JsonModel() = default;

void JsonModel::model_to_json(const SessionModel& model, QJsonObject& json) const
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::to_json() -> Error. Model is not initialized.");

    json[modelKey] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

    for(auto item : model.rootItem()->children()) {
        QJsonObject object;
        item_to_json(item, object);
        itemArray.append(object);
    }

    json[itemsKey] = itemArray;
}

void JsonModel::json_to_model(const QJsonObject& json, SessionModel& model) const
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Model is not initialized.");

    if (model.rootItem()->childrenCount())
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Model is not empty.");

    if (!is_model(json))
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Invalid json object.");

    if (json[modelKey].toString() != QString::fromStdString(model.modelType()))
            throw std::runtime_error("JsonModel::json_to_model() -> Unexpected model type.");

    auto parent = model.rootItem();
    for(const auto ref : json[itemsKey].toArray())
        json_to_item(ref.toObject(), parent);

}

void JsonModel::json_to_item(const QJsonObject& json, SessionItem* parent, int row) const
{
    if (!parent)
        throw std::runtime_error("JsonModel::json_to_item() -> Non initialized item");

    if (!parent->model())
        throw std::runtime_error("JsonModel::json_to_item() -> Item is not a part of the model.");

    if (!is_item(json))
        throw std::runtime_error("JsonModel::json_to_item() -> Error. Given json object can't represent an item.");

    auto modelType = json[modelKey].toString().toStdString();
    auto item = parent->model()->insertNewItem(modelType, parent, row);

    auto itemData = m_itemdata_converter->get_data(json[itemDataKey].toArray());
    item->m_data = std::make_unique<SessionItemData>(itemData);

    // FIXME find more elegant way to replace item registration
    identifier_type identifier = itemData.data(ItemDataRole::IDENTIFIER).value<std::string>();
    parent->model()->manager()->fix_registration(item, identifier);

    parent = item;
    for(const auto ref : json[itemsKey].toArray())
        json_to_item(ref.toObject(), parent);

}

void JsonModel::item_to_json(const SessionItem* item, QJsonObject& json) const
{
    if (!item)
        return;

    json[modelKey] = QString::fromStdString(item->modelType());
    json[itemDataKey] = m_itemdata_converter->get_json(*item->m_data);

    QJsonArray itemArray;
    for (auto child : item->children()) {
        QJsonObject child_json;
        item_to_json(child, child_json);
        itemArray.append(child_json);
    }
    json[itemsKey] = itemArray;
}

bool JsonModel::is_item(const QJsonObject& object) const
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

bool JsonModel::is_model(const QJsonObject& object) const
{
    static const QStringList expected = expected_model_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}

