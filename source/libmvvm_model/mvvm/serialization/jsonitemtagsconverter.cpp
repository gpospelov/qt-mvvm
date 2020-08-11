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
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/model/sessionitemtags.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/tagrow.h>
#include <mvvm/serialization/jsonitemformatassistant.h>
#include <mvvm/serialization/jsonitemtagsconverter.h>
#include <mvvm/serialization/jsontaginfoconverter.h>

using namespace ModelView;

struct JsonItemTagsConverter::JsonItemTagsConverterImpl {
    std::unique_ptr<JsonTagInfoConverterInterface> m_taginfo_converter;
    item_to_json_t item_to_json;
    json_to_item_update_t json_to_item_update;
    json_to_item_t json_to_item;

    JsonItemTagsConverterImpl() { m_taginfo_converter = std::make_unique<JsonTagInfoConverter>(); }

    QJsonObject container_to_json(const SessionItemContainer& container) const
    {
        QJsonObject result;
        result[JsonItemFormatAssistant::tagInfoKey] =
            m_taginfo_converter->to_json(container.tagInfo());

        QJsonArray itemArray;
        for (auto item : container)
            itemArray.append(item_to_json(*item));
        result[JsonItemFormatAssistant::itemsKey] = itemArray;

        return result;
    }
};

JsonItemTagsConverter::JsonItemTagsConverter()
    : p_impl(std::make_unique<JsonItemTagsConverterImpl>())
{
}

JsonItemTagsConverter::~JsonItemTagsConverter() = default;

QJsonObject JsonItemTagsConverter::to_json(const SessionItemTags& tags)
{
    QJsonObject result;
    result[JsonItemFormatAssistant::defaultTagKey] = QString::fromStdString(tags.defaultTag());

    QJsonArray containerArray;
    for (auto container : tags)
        containerArray.append(p_impl->container_to_json(*container));
    result[JsonItemFormatAssistant::containerKey] = containerArray;

    return result;
}

void JsonItemTagsConverter::from_json(const QJsonObject& json, SessionItemTags& item_tags)
{
    static JsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemTags(json))
        throw std::runtime_error(
            "JsonItemTagsConverter::from_json() -> Error. Given json object can't "
            "represent an SessionItemTags.");

    auto default_tag = json[JsonItemFormatAssistant::defaultTagKey].toString().toStdString();

    if (default_tag != item_tags.defaultTag())
        throw std::runtime_error("Default tag mismatch");

    auto container_array = json[JsonItemFormatAssistant::containerKey].toArray();
    if (container_array.size() != item_tags.tagsCount())
        throw std::runtime_error("Number of tags mismatch");

    for (const auto ref : container_array) {
        QJsonObject json_container = ref.toObject();
        TagInfo tagInfo = p_impl->m_taginfo_converter->from_json(
            json_container[JsonItemFormatAssistant::tagInfoKey].toObject());

        if (!item_tags.isTag(tagInfo.name()))
            throw std::runtime_error("No such tag registered");

        if (item_tags.isSinglePropertyTag(tagInfo.name())) {
        } else {
//            for (const auto obj : json_container[JsonItemFormatAssistant::itemsKey].toArray()) {
//                auto item = p_impl->json_to_item(obj.toObject());
//                item_tags.insertItem(item.release(), TagRow::append(tagInfo.name()));
//            }

        }

        //        result->registerTag(tagInfo);
        //        for (const auto obj : json_container[JsonItemFormatAssistant::itemsKey].toArray())
        //        {
        //            auto item = json_to_item(obj.toObject(), parent);
        //            result->insertItem(item.release(), TagRow::append(tagInfo.name()));
        //        }
    }
}
