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
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/model/sessionitemtags.h>
#include <mvvm/model/tagrow.h>
#include <mvvm/serialization/compatibilityutils.h>
#include <mvvm/serialization/jsonitem_types.h>
#include <mvvm/serialization/jsonitemcontainerconverter.h>
#include <mvvm/serialization/jsonitemformatassistant.h>
#include <mvvm/serialization/jsontaginfoconverter.h>

using namespace ModelView;

struct JsonItemContainerConverter::JsonItemContainerConverterImpl {
    std::unique_ptr<JsonTagInfoConverterInterface> m_taginfo_converter;
    ConverterContext m_context;

    JsonItemContainerConverterImpl(ConverterContext context = {}) : m_context(std::move(context))
    {
        m_taginfo_converter = std::make_unique<JsonTagInfoConverter>();
    }

    QJsonObject item_to_json(const SessionItem& item)
    {
        return m_context.m_item_to_json ? m_context.m_item_to_json(item) : QJsonObject();
    }

    void json_to_item_update(const QJsonObject& json, SessionItem* item)
    {
        if (m_context.m_json_to_item_update)
            m_context.m_json_to_item_update(json, item);
    }

    std::unique_ptr<SessionItem> json_to_item(const QJsonObject& json)
    {
        return m_context.m_json_to_item ? m_context.m_json_to_item(json)
                                        : std::unique_ptr<SessionItem>();
    }

    void process_single_property_tag(const QJsonObject& json, SessionItemContainer& container)
    {
        for (const auto obj : json[JsonItemFormatAssistant::itemsKey].toArray())
            json_to_item_update(obj.toObject(), container.itemAt(0));
    }

    void process_universal_property_tag(const QJsonObject& json, SessionItemContainer& container)
    {
        for (const auto obj : json[JsonItemFormatAssistant::itemsKey].toArray()) {
            auto item = json_to_item(obj.toObject());
            if (item)
                container.insertItem(item.release(), container.itemCount());
        }
    }
};

JsonItemContainerConverter::JsonItemContainerConverter()
    : p_impl(std::make_unique<JsonItemContainerConverterImpl>())
{
}

JsonItemContainerConverter::JsonItemContainerConverter(ConverterContext context)
    : p_impl(std::make_unique<JsonItemContainerConverterImpl>(std::move(context)))
{
}

JsonItemContainerConverter::~JsonItemContainerConverter() = default;

QJsonObject JsonItemContainerConverter::to_json(const SessionItemContainer& container)
{
    QJsonObject result;
    result[JsonItemFormatAssistant::tagInfoKey] =
        p_impl->m_taginfo_converter->to_json(container.tagInfo());

    QJsonArray itemArray;
    for (auto item : container)
        itemArray.append(p_impl->item_to_json(*item));
    result[JsonItemFormatAssistant::itemsKey] = itemArray;

    return result;
}

void JsonItemContainerConverter::from_json(const QJsonObject& json, SessionItemContainer& container)
{
    static JsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemContainer(json))
        throw std::runtime_error("Error in JsonItemContainerConverter: given JSON can't represent "
                                 "SessionItemContainer.");

    TagInfo tagInfo = p_impl->m_taginfo_converter->from_json(
        json[JsonItemFormatAssistant::tagInfoKey].toObject());

    if (Compatibility::IsCompatibleSinglePropertyTag(container, tagInfo))
        p_impl->process_single_property_tag(json, container);

    else if (Compatibility::IsCompatibleUniversalTag(container, tagInfo))
        p_impl->process_universal_property_tag(json, container);

    else
        throw std::runtime_error("Error in JsonItemContainerConverter: can't convert json");
}
