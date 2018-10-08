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
QJsonObject from_int(const QVariant& variant);
QVariant to_int(const QJsonObject& variant);

}

QJsonObject json::get_json(const QVariant& variant)
{
    QJsonObject result;

    if (!variant.isValid())
        return from_invalid();
    else if (variant.typeName() == json::int_type_name)
        return from_int(variant);

    throw std::runtime_error("json::get_json() -> Error. Unknown variant type '" +
                             std::string(variant.typeName())+"'.");
}

QVariant json::get_variant(const QJsonObject& object)
{
    QVariant result;

    if (!is_valid(object))
        throw std::runtime_error("json::get_variant() -> Error. Invalid json object");

    const auto variant_type = object[json::variantTypeKey];

    if (variant_type == json::invalid_type_name)
        return QVariant();
    else if(variant_type == json::int_type_name)
        return to_int(object);

    throw std::runtime_error("json::get_variant() -> Error. Invalid json object");
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

QJsonObject from_int(const QVariant& variant)
{
    QJsonObject result;
    result[json::variantTypeKey] = json::int_type_name;
    result[json::variantValueKey] = variant.toInt();
    return result;
}

QVariant to_int(const QJsonObject& object)
{
    return object[json::variantValueKey].toVariant();
}

}
