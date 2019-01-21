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
#include "sessionitem.h"
#include "sessionitemdata.h"
#include "itemutils.h"
#include "itemmanager.h"
#include "customvariants.h"
#include "model_types.h"
#include "sessionmodel.h"
#include <QSet>
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>

using namespace ModelView;

namespace {
QStringList expected_item_keys() {
    QStringList result = QStringList() << JsonItem::modelKey << JsonItem::itemDataKey
                                       << JsonItem::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}

}

const QString ModelView::JsonItem::modelKey = "model";
const QString ModelView::JsonItem::itemDataKey = "itemData";
const QString ModelView::JsonItem::itemsKey = "items";


JsonItem::JsonItem()
    : m_itemdata_converter(new JsonItemData)
{

}

JsonItem::~JsonItem() = default;

void JsonItem::json_to_item(const QJsonObject& json, SessionItem* parent, int row) const
{
    if (!parent)
        throw std::runtime_error("JsonModel::json_to_item() -> Non initialized item");

    if (!parent->model())
        throw std::runtime_error("JsonModel::json_to_item() -> Item is not a part of the model.");

    if (!is_item(json))
        throw std::runtime_error("JsonModel::json_to_item() -> Error. Given json object can't represent an item.");

    auto modelType = json[modelKey].toString().toStdString();
    auto item = parent->model()->insertNewItem(modelType, parent, row);

    auto itemData = m_itemdata_converter->get_data(json[itemDataKey].toArray());
    item->m_data = std::make_unique<SessionItemData>(itemData);

    // FIXME find more elegant way to replace item registration
    identifier_type identifier = itemData.data(ItemDataRole::IDENTIFIER).value<std::string>();
    parent->model()->manager()->fix_registration(item, identifier);

    parent = item;
    for(const auto ref : json[itemsKey].toArray())
        json_to_item(ref.toObject(), parent);

}

void JsonItem::item_to_json(const SessionItem* item, QJsonObject& json) const
{
    if (!item)
        return;

    json[modelKey] = QString::fromStdString(item->modelType());
    json[itemDataKey] = m_itemdata_converter->get_json(*item->m_data);

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

    return true;
}
