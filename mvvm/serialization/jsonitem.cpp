// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonitem.h"
#include "sessionitem.h"
#include "jsonitemdata.h"
#include "jsontaginfo.h"
#include "sessionitemtags.h"
#include "sessionitemcontainer.h"
#include "sessionmodel.h"
#include "itemmanager.h"
#include "sessionitemdata.h"
#include <QJsonObject>
#include <QJsonArray>

using namespace ModelView;

const QString JsonItem::modelKey = "model";
const QString JsonItem::itemDataKey = "itemData";
const QString JsonItem::itemTagsKey = "itemTags";
const QString JsonItem::defaultTagKey = "defaultTag";
const QString JsonItem::containerKey = "containers";
const QString JsonItem::tagInfoKey = "tagInfo";
const QString JsonItem::itemsKey = "items";

JsonItem::JsonItem()
    : m_itemdata_converter(new JsonItemData)
    , m_taginfo_converter(new JsonTagInfo)
{

}

JsonItem::~JsonItem() = default;

QJsonObject JsonItem::to_json(const SessionItem* item) const
{
    QJsonObject result;

    if (!item)
        return result;

    result[modelKey] = QString::fromStdString(item->modelType());
    result[itemDataKey] = m_itemdata_converter->get_json(*item->m_data);
    result[itemTagsKey] = tags_to_json(*item->m_tags.get());

    return result;
}

std::unique_ptr<SessionItem> JsonItem::from_json(const QJsonObject& json) const
{
    auto modelType = json[modelKey].toString().toStdString();

    auto result = m_model->manager()->createItem(modelType);
    result->m_data = m_itemdata_converter->get_data(json[itemDataKey].toArray());
    result->m_tags = json_to_tags(json[itemTagsKey].toObject());

    return result;
}

QJsonObject JsonItem::tags_to_json(const SessionItemTags& tags) const
{
    QJsonObject result;
    result[defaultTagKey] = QString::fromStdString(tags.defaultTag());

    QJsonArray containerArray;
    for (auto container : tags)
        containerArray.append(container_to_json(*container));
    result[containerKey] = containerArray;

    return result;
}

QJsonObject JsonItem::container_to_json(const SessionItemContainer& container) const
{
    QJsonObject result;
    result[tagInfoKey] = m_taginfo_converter->to_json(container.tagInfo());

    QJsonArray itemArray;
    for(auto item: container)
        itemArray.append(to_json(item));
    result[itemsKey] = itemArray;

    return result;
}

std::unique_ptr<SessionItemTags> JsonItem::json_to_tags(const QJsonObject& json) const
{
    auto result = std::make_unique<SessionItemTags>();

    result->setDefaultTag(json[defaultTagKey].toString().toStdString());

    for(const auto ref : json[containerKey].toArray()) {
        QJsonObject json_container = ref.toObject();
        TagInfo tagInfo = m_taginfo_converter->from_json(json_container[tagInfoKey].toObject());
        result->registerTag(tagInfo);
        for(const auto obj : json_container[itemsKey].toArray()) {
            auto item = from_json(obj.toObject());
            result->insertItem(item.release(), -1, tagInfo.name());
        }
    }

    return result;
}


