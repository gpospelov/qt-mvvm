// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonObject>
#include <QJsonArray>
#include <mvvm/model/itemfactoryinterface.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/model/sessionitemtags.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/serialization/jsonitemconverter_v2.h>
#include <mvvm/serialization/jsonitemdataconverter.h>
#include <mvvm/serialization/jsontaginfoconverter.h>
#include <mvvm/serialization/jsonitemformatassistant.h>

using namespace ModelView;

struct JsonItemConverterV2::JsonItemConverterV2Impl {
    const ItemFactoryInterface* m_factory{nullptr};
    bool m_is_new_id{false};
    std::unique_ptr<JsonItemDataConverterInterface> m_itemdata_converter;
    std::unique_ptr<JsonTagInfoConverterInterface> m_taginfo_converter;

    JsonItemConverterV2Impl() {
        m_itemdata_converter = std::make_unique<JsonItemDataConverter>();
        m_taginfo_converter = std::make_unique<JsonTagInfoConverter>();
    }

    const ItemFactoryInterface* factory() { return m_factory; }

    void populate_item_data(const QJsonObject& json, SessionItemData* item_data) {}

    void populate_item_tags(const QJsonObject& json, SessionItemTags* item_tags)
    {
        static JsonItemFormatAssistant assistant;

        if (!assistant.isSessionItemTags(json))
            throw std::runtime_error(
                "JsonItemConverterV2::populate_item_tags() -> Error. Given json object can't "
                "represent an SessionItemTags.");


//        auto default_tag = json[JsonItemFormatAssistant::defaultTagKey].toString().toStdString();

//        if (default_tag != item_tags->defaultTag())
//            throw std::runtime_error("Default tag mismatch");

//        for (const auto ref : json[JsonItemFormatAssistant::containerKey].toArray()) {
//            QJsonObject json_container = ref.toObject();
//            TagInfo tagInfo = m_taginfo_converter->from_json(json_container[JsonItemFormatAssistant::tagInfoKey].toObject());
//            result->registerTag(tagInfo);
//            for (const auto obj : json_container[JsonItemFormatAssistant::itemsKey].toArray()) {
//                auto item = json_to_item(obj.toObject(), parent);
//                result->insertItem(item.release(), TagRow::append(tagInfo.name()));
//            }
//        }
    }

    void populate_item(const QJsonObject& json, SessionItem* item)
    {
        auto modelType = json[JsonItemFormatAssistant::modelKey].toString().toStdString();

        if (modelType != item->modelType())
            throw std::runtime_error("Item model mismatch");

        populate_item_data(json[JsonItemFormatAssistant::itemTagsKey].toObject(),
                                   item->itemData());

        populate_item_tags(json[JsonItemFormatAssistant::itemTagsKey].toObject(),
                                   item->itemTags());
    }

};

JsonItemConverterV2::JsonItemConverterV2(const ItemFactoryInterface* factory, bool new_id_flag)
    : p_impl(std::make_unique<JsonItemConverterV2Impl>())
{
    p_impl->m_factory = factory;
    p_impl->m_is_new_id = new_id_flag;
}

JsonItemConverterV2::~JsonItemConverterV2() = default;

QJsonObject JsonItemConverterV2::to_json(const SessionItem* /*item*/) const
{
    return {};
}

std::unique_ptr<SessionItem> JsonItemConverterV2::from_json(const QJsonObject& json) const
{
    static JsonItemFormatAssistant assistant;

    if (!assistant.isSessionItem(json))
        throw std::runtime_error("JsonItemConverterV2::from_json() -> Error. Given json object "
                                 "can't represent an SessionItem.");

    auto modelType = json[JsonItemFormatAssistant::modelKey].toString().toStdString();
    auto result = p_impl->factory()->createItem(modelType);

    p_impl->populate_item(json, result.get());

    return result;
}
