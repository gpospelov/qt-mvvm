// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonitemformatassistant.h"
#include <QJsonObject>
#include <QStringList>

using namespace ModelView;

namespace {
//! Returns list of keys which should be in QJsonObject to represent SessionItem.
QStringList expected_item_keys()
{
    QStringList result{JsonItemFormatAssistant::modelKey, JsonItemFormatAssistant::itemDataKey,
                       JsonItemFormatAssistant::itemTagsKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemData.

QStringList expected_itemdata_keys()
{
    QStringList result{JsonItemFormatAssistant::roleKey, JsonItemFormatAssistant::variantKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemTags.

QStringList expected_tags_keys()
{
    QStringList result{JsonItemFormatAssistant::defaultTagKey,
                       JsonItemFormatAssistant::containerKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionItemContainer.

QStringList expected_itemcontainer_keys()
{
    QStringList result = {JsonItemFormatAssistant::tagInfoKey, JsonItemFormatAssistant::itemsKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent SessionModel.

QStringList expected_sessionmodel_keys()
{
    QStringList result{JsonItemFormatAssistant::sessionModelKey, JsonItemFormatAssistant::itemsKey};
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace

//! Returns true if given json object represents SessionItem.

bool JsonItemFormatAssistant::isSessionItem(const QJsonObject& json) const
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

bool JsonItemFormatAssistant::isSessionItemData(const QJsonObject& json) const
{
    static const QStringList expected = expected_itemdata_keys();
    return json.keys() == expected;
}

//! Returns true if given json object represents SessionItemTags.

bool JsonItemFormatAssistant::isSessionItemTags(const QJsonObject& json) const
{
    static const QStringList expected = expected_tags_keys();

    if (json.keys() != expected)
        return false;

    if (!json[containerKey].isArray())
        return false;

    return true;
}

//! Returns true if given json object represents SessionItemContainer.

bool JsonItemFormatAssistant::isSessionItemContainer(const QJsonObject& json) const
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

//! Returns true if given json object represents SessionModel.

bool JsonItemFormatAssistant::isSessionModel(const QJsonObject& object) const
{
    static const QStringList expected = expected_sessionmodel_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}
