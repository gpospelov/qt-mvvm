// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonitemtags.h"
#include "obsoletesessionitemtags.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>

using namespace ModelView;

namespace
{
QStringList expected_tags_keys()
{
    QStringList result = QStringList() << JsonItemTags::nameKey << JsonItemTags::minKey
                                       << JsonItemTags::maxKey
                                       << JsonItemTags::modelsKey
                                       << JsonItemTags::countKey;
    std::sort(result.begin(), result.end());
    return result;
}
}

const QString JsonItemTags::nameKey = "name";
const QString JsonItemTags::minKey = "min";
const QString JsonItemTags::maxKey = "max";
const QString JsonItemTags::countKey = "count";
const QString JsonItemTags::modelsKey = "models";

JsonItemTags::JsonItemTags()
{
}

JsonItemTags::~JsonItemTags() = default;

//! Returns array of json objects representing all TagInfo's in SessionItemTags.

QJsonArray JsonItemTags::get_json(const ObsoleteSessionItemTags& itemTags)
{

    QJsonArray result;

    for (const auto& tag : itemTags) {
        QJsonObject object;
        object[nameKey] = QString::fromStdString(tag.name());
        object[minKey] = tag.min();
        object[maxKey] = tag.max();
        object[countKey] = tag.childCount();
        QJsonArray str_array;
        for (const auto& str : tag.modelTypes())
            str_array.append(QString::fromStdString(str));
        object[modelsKey] = str_array;
        result.append(object);
    }

    return result;
}

//! Returns SessionItemTags object reconstructed from its json representation.

ObsoleteSessionItemTags JsonItemTags::get_tags(const QJsonArray& object)
{
    ObsoleteSessionItemTags result;

    for (const auto& json_tag : object) {
        if (!is_item_tag(json_tag.toObject()))
            throw std::runtime_error("JsonItemTags::get_tags() -> Invalid json object.");

        auto name = json_tag[nameKey].toString().toStdString();
        auto min = json_tag[minKey].toInt();
        auto max = json_tag[maxKey].toInt();
        auto count = json_tag[countKey].toInt();
        std::vector<std::string> models;
        for(const auto ref : json_tag[modelsKey].toArray()) {
            models.push_back(ref.toString().toStdString());
        }
        TagInfo tag(name, min, max, models);
        tag.setCount(count); // FIXME remove after refactoring
        result.registerTag(tag);
    }

    return result;
}

//! Returns true if given json objects represents TagInfo.

bool JsonItemTags::is_item_tag(const QJsonObject& object)
{
    static const QStringList expected = expected_tags_keys();

    if (object.keys() != expected)
        return false;

    if (!object[modelsKey].isArray())
        return false;

    return true;
}
