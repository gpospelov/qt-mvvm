// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonmodelconverter.h"
#include "mvvm/factories/itemconverterfactory.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/serialization/jsonitem_types.h"
#include "mvvm/serialization/jsonitemformatassistant.h"
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>

using namespace ModelView;

namespace {
std::unique_ptr<JsonItemConverterInterface> CreateConverter(const ItemFactoryInterface* factory,
                                                            ConverterMode mode)
{
    if (mode == ConverterMode::clone)
        return CreateItemCloneConverter(factory);
    else if (mode == ConverterMode::copy)
        return CreateItemCopyConverter(factory);
    else if (mode == ConverterMode::project)
        return CreateItemProjectConverter(factory);
    else
        throw std::runtime_error("Error in JsonModelConverter: unknown converter mode");
}

} // namespace

JsonModelConverter::JsonModelConverter(ConverterMode mode) : m_mode(mode) {}

JsonModelConverter::~JsonModelConverter() = default;

QJsonObject JsonModelConverter::to_json(const SessionModel& model) const
{
    QJsonObject result;

    if (!model.rootItem())
        throw std::runtime_error("JsonModel::to_json() -> Error. Model is not initialized.");

    result[JsonItemFormatAssistant::sessionModelKey] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

    auto itemConverter = CreateConverter(model.factory(), m_mode);

    for (auto item : model.rootItem()->children())
        itemArray.append(itemConverter->to_json(item));

    result[JsonItemFormatAssistant::itemsKey] = itemArray;

    return result;
}

void JsonModelConverter::from_json(const QJsonObject& json, SessionModel& model) const
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

    auto itemConverter = CreateConverter(model.factory(), m_mode);

    auto rebuild_root = [&json, &itemConverter](auto parent) {
        for (const auto ref : json[JsonItemFormatAssistant::itemsKey].toArray()) {
            parent->insertItem(itemConverter->from_json(ref.toObject()), TagRow::append());
        }
    };
    model.clear(rebuild_root);
}
