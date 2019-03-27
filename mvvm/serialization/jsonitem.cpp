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

    return {};
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


