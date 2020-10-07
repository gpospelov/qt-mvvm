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
#include <mvvm/model/sessionitemtags.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/serialization/jsonitem_types.h>
#include <mvvm/serialization/jsonitemcontainerconverter.h>
#include <mvvm/serialization/jsonitemformatassistant.h>
#include <mvvm/serialization/jsonitemtagsconverter.h>
#include <mvvm/serialization/jsontaginfoconverter.h>

using namespace ModelView;

struct JsonItemTagsConverter::JsonItemTagsConverterImpl {
    std::unique_ptr<JsonItemContainerConverter> m_container_converter;
    std::unique_ptr<JsonTagInfoConverterInterface> m_taginfo_converter;

    JsonItemTagsConverterImpl(ConverterCallbacks callbacks = {})
    {
        m_container_converter = std::make_unique<JsonItemContainerConverter>(std::move(callbacks));
        m_taginfo_converter = std::make_unique<JsonTagInfoConverter>();
    }

    void populate_container(const QJsonObject& json, SessionItemContainer& container)
    {
        m_container_converter->from_json(json, container);
    }

    //! Populate containers from JSON. Container must be already created.

    void populate_containers(const QJsonObject& json, SessionItemTags& item_tags)
    {
        auto container_array = json[JsonItemFormatAssistant::containerKey].toArray();

        if (container_array.size() != item_tags.tagsCount())
            throw std::runtime_error("Error in JsonItemTagsConverter: mismatch in number of tags");

        int index(0);
        for (const auto container_ref : container_array)
            m_container_converter->from_json(container_ref.toObject(), item_tags.at(index++));
    }
};

JsonItemTagsConverter::JsonItemTagsConverter(ConverterCallbacks callbacks)
    : p_impl(std::make_unique<JsonItemTagsConverterImpl>(callbacks))
{
}

JsonItemTagsConverter::~JsonItemTagsConverter() = default;

QJsonObject JsonItemTagsConverter::to_json(const SessionItemTags& tags)
{
    QJsonObject result;
    result[JsonItemFormatAssistant::defaultTagKey] = QString::fromStdString(tags.defaultTag());

    QJsonArray containerArray;
    for (auto container : tags)
        containerArray.append(p_impl->m_container_converter->to_json(*container));
    result[JsonItemFormatAssistant::containerKey] = containerArray;

    return result;
}

// TODO allow strict version below too

// void JsonItemTagsConverter::from_json(const QJsonObject& json, SessionItemTags& item_tags)
//{
//    static JsonItemFormatAssistant assistant;

//    if (!assistant.isSessionItemTags(json))
//        throw std::runtime_error(
//            "JsonItemTagsConverter::from_json() -> Error. Given json object can't "
//            "represent a SessionItemTags.");

//    auto default_tag = json[JsonItemFormatAssistant::defaultTagKey].toString().toStdString();

//    if (default_tag != item_tags.defaultTag())
//        throw std::runtime_error("Default tag mismatch");

//    auto container_array = json[JsonItemFormatAssistant::containerKey].toArray();

//    // FIXME: JSON contains SessionItemContainers not presented at runtime, what to do?
//    // If user register tags after object construction, shell it be serialized, or not?
//    // It is easy to recreate, but what about back compatibility?
//    // Consider container recreation.
//    if (container_array.size() != item_tags.tagsCount())
//        throw std::runtime_error("Error in JsonItemTagsConverter: number of tags mismatch.");

//    int index(0);
//    for (const auto ref : container_array) {
//        QJsonObject json_container = ref.toObject();
//        p_impl->populate_container(json_container, item_tags.at(++index));
//    }
//}

//! Reconstructs SessionItemTags from the content of JSON object.
//! Can work in two modes:
//! + If SessionItemTags is empty, all tags will be reconstructed as in JSON, and then populated
//!   with the content.
//! + If SessionItemTags contains some tags already, they will be populated from JSON. in this
//!   case it will be assumed, that tag names matching JSON.

void JsonItemTagsConverter::from_json(const QJsonObject& json, SessionItemTags& item_tags)
{
    static JsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemTags(json))
        throw std::runtime_error(
            "Error in JsonItemTagsConverter: given json object can't represent a SessionItemTags.");

    auto default_tag = json[JsonItemFormatAssistant::defaultTagKey].toString().toStdString();
    item_tags.setDefaultTag(default_tag);

    auto container_array = json[JsonItemFormatAssistant::containerKey].toArray();

    for (const auto ref : container_array) {
        QJsonObject json_container = ref.toObject();
        QJsonObject json_taginfo = json_container[JsonItemFormatAssistant::tagInfoKey].toObject();
        TagInfo tagInfo = p_impl->m_taginfo_converter->from_json(json_taginfo);
        item_tags.registerTag(tagInfo);
    }

    p_impl->populate_containers(json, item_tags);
}
