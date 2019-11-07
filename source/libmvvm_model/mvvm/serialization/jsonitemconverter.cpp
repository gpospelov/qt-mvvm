// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/serialization/jsonitemconverter.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/itemfactoryinterface.h>
#include <mvvm/serialization/jsonitemdata.h>
#include <mvvm/serialization/jsontaginfo.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/model/sessionitemtags.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/uniqueidgenerator.h>
#include <QJsonArray>
#include <QJsonObject>

namespace
{
QStringList expected_item_keys();
QStringList expected_tags_keys();
QStringList expected_itemcontainer_keys();
} // namespace

using namespace ModelView;

const QString JsonItemConverter::modelKey = "model";
const QString JsonItemConverter::itemDataKey = "itemData";
const QString JsonItemConverter::itemTagsKey = "itemTags";

const QString JsonItemConverter::defaultTagKey = "defaultTag";
const QString JsonItemConverter::containerKey = "containers";

const QString JsonItemConverter::tagInfoKey = "tagInfo";
const QString JsonItemConverter::itemsKey = "items";

//! Constructor of item/json converter.
//! @param factory: SessionItem factory.
//! @param new_id_flag: generates exact item clones if false, generates new item's unique
//! identifiers if true.

JsonItemConverter::JsonItemConverter(const ItemFactoryInterface* factory, bool new_id_flag)
    : m_itemdata_converter(std::make_unique<JsonItemData>()),
      m_taginfo_converter(std::make_unique<JsonTagInfo>()), m_factory(factory),
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

//! Returns true if given json object represents SessionItem.

bool JsonItemConverter::isSessionItem(const QJsonObject& json) const
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

bool JsonItemConverter::isSessionItemTags(const QJsonObject& json) const
{
    static const QStringList expected = expected_tags_keys();

    if (json.keys() != expected)
        return false;

    if (!json[containerKey].isArray())
        return false;

    return true;
}

//! Returns true if given json object represents SessionItemContainer.

bool JsonItemConverter::isSessionItemContainer(const QJsonObject& json) const
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
    if (!isSessionItem(json))
        throw std::runtime_error(
            "JsonItem::from_json() -> Error. Given json object can't represent an SessionItem.");

    auto modelType = json[modelKey].toString().toStdString();
    auto result = m_factory->createItem(modelType);
    result->setParent(parent);

    result->setDataAndTags(m_itemdata_converter->get_data(json[itemDataKey].toArray()), json_to_tags(json[itemTagsKey].toObject(), result.get()));

    if (m_generate_new_identifiers)
        result->setData(QVariant::fromValue(UniqueIdGenerator::generate()),
                        ItemDataRole::IDENTIFIER);

    return result;
}

std::unique_ptr<SessionItemTags> JsonItemConverter::json_to_tags(const QJsonObject& json,
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
            result->insertItem(item.release(), TagRow::append(tagInfo.name()));
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
                         << JsonItemConverter::modelKey << JsonItemConverter::itemDataKey
                         << JsonItemConverter::itemTagsKey;
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemTags.

QStringList expected_tags_keys()
{
    QStringList result = QStringList()
                         << JsonItemConverter::defaultTagKey << JsonItemConverter::containerKey;
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemContainer.

QStringList expected_itemcontainer_keys()
{
    QStringList result = QStringList()
                         << JsonItemConverter::tagInfoKey << JsonItemConverter::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace
