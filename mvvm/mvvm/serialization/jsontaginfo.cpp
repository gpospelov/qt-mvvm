// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/serialization/jsontaginfo.h>
#include <mvvm/model/taginfo.h>
#include <QJsonArray>
#include <QString>
#include <QStringList>

namespace
{
QStringList expected_taginfo_keys();
}

using namespace ModelView;

const QString JsonTagInfo::nameKey = "name";
const QString JsonTagInfo::minKey = "min";
const QString JsonTagInfo::maxKey = "max";
const QString JsonTagInfo::modelsKey = "models";

QJsonObject JsonTagInfo::to_json(const ModelView::TagInfo& tag)
{
    QJsonObject result;
    result[nameKey] = QString::fromStdString(tag.name());
    result[minKey] = tag.min();
    result[maxKey] = tag.max();
    QJsonArray str_array;
    for (const auto& str : tag.modelTypes())
        str_array.append(QString::fromStdString(str));
    result[modelsKey] = str_array;

    return result;
}

TagInfo JsonTagInfo::from_json(const QJsonObject& object)
{
    if (!isTagInfo(object))
        throw std::runtime_error("JsonTagInfo::get_tags() -> Invalid json object.");

    auto name = object[nameKey].toString().toStdString();
    auto min = object[minKey].toInt();
    auto max = object[maxKey].toInt();
    std::vector<std::string> models;
    for (const auto ref : object[modelsKey].toArray())
        models.push_back(ref.toString().toStdString());

    return TagInfo(name, min, max, models);
}

//! Returns true if given json object represents TagInfo object.

bool JsonTagInfo::isTagInfo(const QJsonObject& object)
{
    static const QStringList expected = expected_taginfo_keys();

    if (object.keys() != expected)
        return false;

    if (!object[modelsKey].isArray())
        return false;

    return true;
}

namespace
{
QStringList expected_taginfo_keys()
{
    QStringList result = QStringList() << JsonTagInfo::nameKey << JsonTagInfo::minKey
                                       << JsonTagInfo::maxKey << JsonTagInfo::modelsKey;
    std::sort(result.begin(), result.end());
    return result;
}
} // namespace
