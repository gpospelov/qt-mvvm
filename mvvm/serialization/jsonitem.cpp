// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonitem.h"
#include "jsonitemdata.h"
#include "jsonitemtags.h"
#include "sessionitem.h"
#include "sessionitemdata.h"
#include "sessionitemtags.h"
#include "itemutils.h"
#include "itemmanager.h"
#include "customvariants.h"
#include "model_types.h"
#include "sessionmodel.h"
#include <QSet>
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>
#include <sstream>

using namespace ModelView;

namespace {
QStringList expected_item_keys() {
    QStringList result = QStringList() << JsonItem::modelKey << JsonItem::parentTagKey
                                       << JsonItem::itemDataKey << JsonItem::itemTagsKey
                                       << JsonItem::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}

}

const QString ModelView::JsonItem::modelKey = "model";
const QString ModelView::JsonItem::parentTagKey = "parentTag";
const QString ModelView::JsonItem::itemDataKey = "itemData";
const QString ModelView::JsonItem::itemTagsKey = "itemTags";
const QString ModelView::JsonItem::itemsKey = "items";


JsonItem::JsonItem()
    : m_itemdata_converter(new JsonItemData)
    , m_itemtags_converter(new JsonItemTags)
{

}

JsonItem::~JsonItem() = default;

void JsonItem::json_to_item(const QJsonObject& json, SessionItem* parent, int row, const std::string& tag) const
{
    if (!parent)
        throw std::runtime_error("JsonModel::json_to_item() -> Non initialized item");

    if (!parent->model())
        throw std::runtime_error("JsonModel::json_to_item() -> Item is not a part of the model.");

    if (!is_item(json))
        throw std::runtime_error("JsonModel::json_to_item() -> Error. Given json object can't represent an item.");

    auto modelType = json[modelKey].toString().toStdString();
    auto parentTag = json[parentTagKey].toString().toStdString();

    auto item = parent->model()->insertNewItem(modelType, parent, row, parentTag);
//    auto item = parent->model()->insertNewItem(modelType, parent, row, tag);

    auto itemData = m_itemdata_converter->get_data(json[itemDataKey].toArray());
    item->m_data = std::make_unique<SessionItemData>(itemData);

    auto itemTags = m_itemtags_converter->get_tags(json[itemTagsKey].toArray());
    // FIXME remove hack after refactoring of SessionItemData
    itemTags.resetTags();
    item->m_tags = std::make_unique<SessionItemTags>(itemTags);
//    auto tagSummary = item->m_tags->tagsSummary();

    // FIXME find more elegant way to replace item registration
    identifier_type identifier = itemData.data(ItemDataRole::IDENTIFIER).value<std::string>();
    parent->model()->manager()->fix_registration(item, identifier);

    parent = item;

//    if (static_cast<int>(tagSummary.size()) != json[itemsKey].toArray().size()) {
//        std::ostringstream ostr;
//        ostr << "JsonItem::json_to_item() -> Size of json array " << json[itemsKey].toArray().size()
//             << " does not match tag summary size " << tagSummary.size();
//        throw std::runtime_error(ostr.str());
//    }

//    size_t index(0);
//    for(const auto ref : json[itemsKey].toArray()) {

//        json_to_item(ref.toObject(), parent, tagSummary[index].first, tagSummary[index].second);
//        index++;
//    }


    for(const auto ref : json[itemsKey].toArray())
        json_to_item(ref.toObject(), parent);
}

void JsonItem::item_to_json(const SessionItem* item, QJsonObject& json) const
{
    if (!item)
        return;

    json[modelKey] = QString::fromStdString(item->modelType());

    std::string parentTag = item->parent() ? item->parent()->tagFromItem(item) : "";
    json[parentTagKey] = QString::fromStdString(parentTag);
    json[itemDataKey] = m_itemdata_converter->get_json(*item->m_data);
    json[itemTagsKey] = m_itemtags_converter->get_json(*item->m_tags);

    QJsonArray itemArray;
    for (auto child : item->children()) {
        QJsonObject child_json;
        item_to_json(child, child_json);
        itemArray.append(child_json);
    }
    json[itemsKey] = itemArray;
}

bool JsonItem::is_item(const QJsonObject& object) const
{
    static const QStringList expected = expected_item_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    if (!object[itemDataKey].isArray())
        return false;

    if (!object[itemTagsKey].isArray())
        return false;

    return true;
}
