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
#include "customvariants.h"
#include "mvvm_types.h"
#include "jsonitemconverter.h"
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
{

}

JsonModel::~JsonModel() = default;

void JsonModel::model_to_json(const SessionModel& model, QJsonObject& json) const
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

void JsonModel::json_to_model(const QJsonObject& json, SessionModel& model) const
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

bool JsonModel::isSessionModel(const QJsonObject& object) const
{
    static const QStringList expected = expected_model_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}

