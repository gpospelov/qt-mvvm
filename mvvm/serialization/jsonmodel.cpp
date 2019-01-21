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
#include "jsonitem.h"
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
QStringList expected_model_keys() {
    QStringList result = QStringList() << JsonModel::modelKey << JsonModel::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}


}

const QString ModelView::JsonModel::modelKey = "model";
const QString ModelView::JsonModel::itemsKey = "items";
const QString ModelView::JsonModel::versionKey = "version";


JsonModel::JsonModel()
    : m_item_converter(new JsonItem)
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
        m_item_converter->item_to_json(item, object);
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
        m_item_converter->json_to_item(ref.toObject(), parent);

}

void JsonModel::json_to_item(const QJsonObject& json, SessionItem* parent, int row) const
{
    return m_item_converter->json_to_item(json, parent, row);
}

void JsonModel::item_to_json(const SessionItem* item, QJsonObject& json) const
{
    return m_item_converter->item_to_json(item, json);
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

