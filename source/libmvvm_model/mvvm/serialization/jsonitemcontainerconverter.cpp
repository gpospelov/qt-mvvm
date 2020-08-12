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

    JsonItemContainerConverterImpl()
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
};

JsonItemContainerConverter::JsonItemContainerConverter()
    : p_impl(std::make_unique<JsonItemContainerConverterImpl>())
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

    if (Compatibility::IsCompatibleSingleProperty(container, tagInfo))
        p_impl->json_to_item_update(json, container.itemAt(0));
}
