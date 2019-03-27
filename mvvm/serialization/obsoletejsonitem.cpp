// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "obsoletejsonitem.h"
#include "jsonitemdata.h"
#include "obsoletejsonitemtags.h"
#include "sessionitem.h"
#include "sessionitemdata.h"
#include "obsoletesessionitemtags.h"
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
    QStringList result = QStringList() << ObsoleteJsonItem::modelKey << ObsoleteJsonItem::parentTagKey
                                       << ObsoleteJsonItem::itemDataKey << ObsoleteJsonItem::itemTagsKey
                                       << ObsoleteJsonItem::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}

}

const QString ModelView::ObsoleteJsonItem::modelKey = "model";
const QString ModelView::ObsoleteJsonItem::parentTagKey = "parentTag";
const QString ModelView::ObsoleteJsonItem::itemDataKey = "itemData";
const QString ModelView::ObsoleteJsonItem::itemTagsKey = "itemTags";
const QString ModelView::ObsoleteJsonItem::itemsKey = "items";


ObsoleteJsonItem::ObsoleteJsonItem()
    : m_itemdata_converter(new JsonItemData)
    , m_itemtags_converter(new ObsoleteJsonItemTags)
{

}

ObsoleteJsonItem::~ObsoleteJsonItem() = default;

void ObsoleteJsonItem::json_to_item(const QJsonObject& json, SessionItem* parent, int row, const std::string& tag) const
{
    if (!parent)
        throw std::runtime_error("JsonModel::json_to_item() -> Non initialized item");

    if (!parent->model())
        throw std::runtime_error("JsonModel::json_to_item() -> Item is not a part of the model.");

    if (!is_item(json))
        throw std::runtime_error("JsonModel::json_to_item() -> Error. Given json object can't represent an item.");

    auto modelType = json[modelKey].toString().toStdString();
//    auto parentTag = json[parentTagKey].toString().toStdString();

//    auto item = parent->model()->insertNewItem(modelType, parent, row, parentTag);
    auto item = parent->model()->insertNewItem(modelType, parent, row, tag);

    item->m_data = m_itemdata_converter->get_data(json[itemDataKey].toArray());

    auto itemTags = m_itemtags_converter->get_tags(json[itemTagsKey].toArray());

    item->m_obsolete_tags = std::make_unique<ObsoleteSessionItemTags>(itemTags);

    // FIXME find more elegant way to replace item registration
    identifier_type identifier = item->data(ItemDataRole::IDENTIFIER).value<std::string>();
    parent->model()->manager()->fix_registration(item, identifier);

    parent = item;
    auto tagSummary = parent->m_obsolete_tags->tagsSummary();
    parent->m_obsolete_tags->resetTags(); // FIXME remove hack

    if (static_cast<int>(tagSummary.size()) != json[itemsKey].toArray().size()) {
        std::ostringstream ostr;
        ostr << "JsonItem::json_to_item() -> Size of json array " << json[itemsKey].toArray().size()
             << " does not match tag summary size " << tagSummary.size();
        throw std::runtime_error(ostr.str());
    }

    size_t index(0);
    for(const auto ref : json[itemsKey].toArray()) {

        json_to_item(ref.toObject(), parent, tagSummary[index].first, tagSummary[index].second);
        index++;
    }
}

void ObsoleteJsonItem::item_to_json(const SessionItem* item, QJsonObject& json) const
{
    if (!item)
        return;

    json[modelKey] = QString::fromStdString(item->modelType());

    std::string parentTag = item->parent() ? item->parent()->tagFromItem(item) : "";
    json[parentTagKey] = QString::fromStdString(parentTag);
    json[itemDataKey] = m_itemdata_converter->get_json(*item->m_data);
    json[itemTagsKey] = m_itemtags_converter->get_json(*item->m_obsolete_tags);

    QJsonArray itemArray;
    for (auto child : item->children()) {
        QJsonObject child_json;
        item_to_json(child, child_json);
        itemArray.append(child_json);
    }
    json[itemsKey] = itemArray;
}

bool ObsoleteJsonItem::is_item(const QJsonObject& object) const
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
