// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonitem.h"
#include "itemmanager.h"
#include "jsonitemdata.h"
#include "jsontaginfo.h"
#include "sessionitem.h"
#include "sessionitemcontainer.h"
#include "sessionitemdata.h"
#include "sessionitemtags.h"
#include "sessionmodel.h"
#include "itemfactoryinterface.h"
#include "sessionitem_p.h"
#include <QJsonArray>
#include <QJsonObject>

namespace
{
QStringList expected_item_keys();
QStringList expected_tags_keys();
QStringList expected_itemcontainer_keys();
} // namespace

using namespace ModelView;

const QString JsonItem::modelKey = "model";
const QString JsonItem::itemDataKey = "itemData";
const QString JsonItem::itemTagsKey = "itemTags";

const QString JsonItem::defaultTagKey = "defaultTag";
const QString JsonItem::containerKey = "containers";

const QString JsonItem::tagInfoKey = "tagInfo";
const QString JsonItem::itemsKey = "items";

JsonItem::JsonItem(const SessionModel* model)
    : m_itemdata_converter(std::make_unique<JsonItemData>()),
      m_taginfo_converter(std::make_unique<JsonTagInfo>()), m_factory(nullptr)
{
    m_factory = model->manager()->factory();
}

JsonItem::JsonItem(const ItemFactoryInterface* factory)
    : m_itemdata_converter(std::make_unique<JsonItemData>()),
      m_taginfo_converter(std::make_unique<JsonTagInfo>()), m_factory(factory)
{

}

JsonItem::~JsonItem() = default;

QJsonObject JsonItem::to_json(const SessionItem* item) const
{
    if (!item)
        return QJsonObject();

    return item_to_json(*item);
}

std::unique_ptr<SessionItem> JsonItem::from_json(const QJsonObject& json) const
{
    return json_to_item(json);
}

//! Returns true if given json object represents SessionItem.

bool JsonItem::isSessionItem(const QJsonObject& json) const
{
    static const QStringList expected = expected_item_keys();

    if (json.keys() != expected)
        return false;

    if (!json[itemDataKey].isArray())
        return false;

    if (!json[itemTagsKey].isObject())
        return false;

    return true;
}

//! Returns true if given json object represents SessionItemTags.

bool JsonItem::isSessionItemTags(const QJsonObject& json) const
{
    static const QStringList expected = expected_tags_keys();

    if (json.keys() != expected)
        return false;

    if (!json[containerKey].isArray())
        return false;

    return true;
}

//! Returns true if given json object represents SessionItemContainer.

bool JsonItem::isSessionItemContainer(const QJsonObject& json) const
{
    static const QStringList expected = expected_itemcontainer_keys();

    if (json.keys() != expected)
        return false;

    if (!json[tagInfoKey].isObject())
        return false;

    if (!json[itemsKey].isArray())
        return false;

    return true;
}

// --- to json --------------------------------------------------------

//! Converts SessionItem to json object.

QJsonObject JsonItem::item_to_json(const SessionItem& item) const
{
    QJsonObject result;
    result[modelKey] = QString::fromStdString(item.modelType());
    result[itemDataKey] = m_itemdata_converter->get_json(*item.p_impl->m_data);
    result[itemTagsKey] = tags_to_json(*item.p_impl->m_tags.get());

    return result;
}

//! Converts SessionItemTags to json object.

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

//! Converts SessionItemContainer to json object.

QJsonObject JsonItem::container_to_json(const SessionItemContainer& container) const
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

std::unique_ptr<SessionItem> JsonItem::json_to_item(const QJsonObject& json,
                                                    SessionItem* parent) const
{
    if (!isSessionItem(json))
        throw std::runtime_error(
            "JsonItem::from_json() -> Error. Given json object can't represent an SessionItem.");

    auto modelType = json[modelKey].toString().toStdString();
    auto result = m_factory->createItem(modelType);
    result->setParent(parent);

    result->p_impl->m_data = m_itemdata_converter->get_data(json[itemDataKey].toArray());
    result->p_impl->m_tags = json_to_tags(json[itemTagsKey].toObject(), result.get());

    return result;
}

std::unique_ptr<SessionItemTags> JsonItem::json_to_tags(const QJsonObject& json,
                                                        SessionItem* parent) const
{
    if (!isSessionItemTags(json))
        throw std::runtime_error("JsonItem::json_to_tags() -> Error. Given json object can't "
                                 "represent an SessionItemTags.");

    auto result = std::make_unique<SessionItemTags>();
    result->setDefaultTag(json[defaultTagKey].toString().toStdString());

    for (const auto ref : json[containerKey].toArray()) {
        QJsonObject json_container = ref.toObject();
        TagInfo tagInfo = m_taginfo_converter->from_json(json_container[tagInfoKey].toObject());
        result->registerTag(tagInfo);
        for (const auto obj : json_container[itemsKey].toArray()) {
            auto item = json_to_item(obj.toObject(), parent);
            result->insertItem(item.release(), tagInfo.name(), -1);
        }
    }

    return result;
}

// --- Utilities --------------------------------------------------------------

namespace
{

//! Returns list of keys which should be in QJsonObject to represent SessionItem.

QStringList expected_item_keys()
{
    QStringList result = QStringList()
                         << JsonItem::modelKey << JsonItem::itemDataKey << JsonItem::itemTagsKey;
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemTags.

QStringList expected_tags_keys()
{
    QStringList result = QStringList() << JsonItem::defaultTagKey << JsonItem::containerKey;
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemContainer.

QStringList expected_itemcontainer_keys()
{
    QStringList result = QStringList() << JsonItem::tagInfoKey << JsonItem::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace
