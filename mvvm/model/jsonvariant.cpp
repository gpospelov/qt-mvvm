// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonvariant.h"
#include "jsonkeys.h"
#include <QJsonObject>
#include <stdexcept>
#include <sstream>

namespace {

bool is_valid(const QJsonObject& json);
QJsonObject from_invalid();

}

QJsonObject json::get_json(const QVariant& variant)
{
    QJsonObject result;

    if (!variant.isValid())
        return from_invalid();

    throw std::runtime_error("json::get_json() -> Error. Unknown variant type '" +
                             std::string(variant.typeName())+"'.");
}

QVariant json::get_variant(const QJsonObject& object)
{
    QVariant result;

    if (!is_valid(object))
        throw std::runtime_error("json::get_variant() -> Error. Invalid json object");

    return result;
}

namespace {

bool is_valid(const QJsonObject& json)
{
    static const QStringList expected = QStringList() << json::variantTypeKey << json::variantValueKey;
    return json.keys() == expected ? true : false;
}

QJsonObject from_invalid()
{
    QJsonObject result;
    result[json::variantTypeKey] = json::invalid_type_name;
    result[json::variantValueKey] = QJsonValue();
    return result;
}
}
