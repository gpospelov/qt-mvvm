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
#include <mvvm/core/uniqueidgenerator.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/itemfactoryinterface.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/model/sessionitemtags.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/serialization/compatibilityutils.h>
#include <mvvm/serialization/jsonitemconverter.h>
#include <mvvm/serialization/jsonitemdataconverter.h>
#include <mvvm/serialization/jsonitemformatassistant.h>
#include <mvvm/serialization/jsontaginfoconverter.h>
#include <stdexcept>

using namespace ModelView;

//! Constructor of item/json converter.
//! @param factory: SessionItem factory.
//! @param new_id_flag: generates exact item clones if false, generates new item's unique
//! identifiers if true.

JsonItemConverter::JsonItemConverter(const ItemFactoryInterface* factory, bool new_id_flag)
    : m_itemdata_converter(std::make_unique<JsonItemDataConverter>()),
      m_taginfo_converter(std::make_unique<JsonTagInfoConverter>()), m_factory(factory),
      m_generate_new_identifiers(new_id_flag)
{
}

JsonItemConverter::~JsonItemConverter() = default;

QJsonObject JsonItemConverter::to_json(const SessionItem* item) const
{
    if (!item)
        return QJsonObject();

    return item_to_json(*item);
}

std::unique_ptr<SessionItem> JsonItemConverter::from_json(const QJsonObject& json) const
{
    return json_to_item(json);
}

// --- to json --------------------------------------------------------

//! Converts SessionItem to json object.

QJsonObject JsonItemConverter::item_to_json(const SessionItem& item) const
{
    QJsonObject result;
    result[modelKey] = QString::fromStdString(item.modelType());
    result[itemDataKey] = m_itemdata_converter->get_json(*item.itemData());
    result[itemTagsKey] = tags_to_json(*item.itemTags());

    return result;
}

//! Converts SessionItemTags to json object.

QJsonObject JsonItemConverter::tags_to_json(const SessionItemTags& tags) const
{
    QJsonObject result;
    result[defaultTagKey] = QString::fromStdString(tags.defaultTag());

    QJsonArray containerArray;
    for (auto container : tags)
        containerArray.append(container_to_json(*container));
    result[containerKey] = containerArray;

    return result;
}

//! Converts SessionItemContainer to json object.

QJsonObject JsonItemConverter::container_to_json(const SessionItemContainer& container) const
{
    QJsonObject result;
    result[tagInfoKey] = m_taginfo_converter->to_json(container.tagInfo());

    QJsonArray itemArray;
    for (auto item : container)
        itemArray.append(item_to_json(*item));
    result[itemsKey] = itemArray;

    return result;
}

// --- from json --------------------------------------------------------------

std::unique_ptr<SessionItem> JsonItemConverter::json_to_item(const QJsonObject& json,
                                                             SessionItem* parent) const
{
    static JsonItemFormatAssistant assistant;

    if (!assistant.isSessionItem(json))
        throw std::runtime_error("JsonItemConverter::from_json() -> Error. Given json object can't "
                                 "represent an SessionItem.");

    auto modelType = json[modelKey].toString().toStdString();
    auto result = m_factory->createItem(modelType);
    result->setParent(parent);

    auto persistent_tags = json_to_tags(json[itemTagsKey].toObject(), result.get());
    auto persistent_data = m_itemdata_converter->get_data(json[itemDataKey].toArray());
    auto combined = Compatibility::CombineItemData(*result->itemData(), *persistent_data.get());

    result->setDataAndTags(std::move(combined), std::move(persistent_tags));

    if (m_generate_new_identifiers)
        result->setData(UniqueIdGenerator::generate(), ItemDataRole::IDENTIFIER);

    return result;
}

std::unique_ptr<SessionItemTags> JsonItemConverter::json_to_tags(const QJsonObject& json,
                                                                 SessionItem* parent) const
{
    static JsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemTags(json))
        throw std::runtime_error(
            "JsonItemConverter::json_to_tags() -> Error. Given json object can't "
            "represent an SessionItemTags.");

    auto result = std::make_unique<SessionItemTags>();
    result->setDefaultTag(json[defaultTagKey].toString().toStdString());

    for (const auto ref : json[containerKey].toArray()) {
        QJsonObject json_container = ref.toObject();
        TagInfo tagInfo = m_taginfo_converter->from_json(json_container[tagInfoKey].toObject());
        result->registerTag(tagInfo);
        for (const auto obj : json_container[itemsKey].toArray()) {
            auto item = json_to_item(obj.toObject(), parent);
            result->insertItem(item.release(), TagRow::append(tagInfo.name()));
        }
    }

    return result;
}
