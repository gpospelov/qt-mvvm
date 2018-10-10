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
#include <QJsonArray>
#include <stdexcept>
#include <sstream>
#include <customvariants.h>
#include <QDebug>

namespace {

bool is_valid(const QJsonObject& json);
QJsonObject from_invalid();

QJsonObject from_int(const QVariant& variant);
QVariant to_int(const QJsonObject& object);

QJsonObject from_string(const QVariant& variant);
QVariant to_string(const QJsonObject& object);

QJsonObject from_double(const QVariant& variant);
QVariant to_double(const QJsonObject& object);

QJsonObject from_vector_double(const QVariant& variant);
QVariant to_vector_double(const QJsonObject& object);

}

QJsonObject json::get_json(const QVariant& variant)
{
    QJsonObject result;

    const QString type_name = variant.typeName();

    if (!variant.isValid())
        return from_invalid();

    else if (type_name == json::int_type_name)
        return from_int(variant);

    else if (type_name == json::string_type_name)
        return from_string(variant);

    else if (type_name == json::double_type_name)
        return from_double(variant);

    else if (type_name == json::vector_double_type_name)
        return from_vector_double(variant);

    throw std::runtime_error("json::get_json() -> Error. Unknown variant type '" +
                             std::string(variant.typeName())+"'.");
}

QVariant json::get_variant(const QJsonObject& object)
{
    QVariant result;

    if (!is_valid(object))
        throw std::runtime_error("json::get_variant() -> Error. Invalid json object");

    const auto variant_type = object[json::variantTypeKey].toString();

    if (variant_type == json::invalid_type_name)
        return QVariant();

    else if(variant_type == json::int_type_name)
        return to_int(object);

    else if(variant_type == json::string_type_name)
        return to_string(object);

    else if(variant_type == json::double_type_name)
        return to_double(object);

    else if(variant_type == json::vector_double_type_name)
        return to_vector_double(object);

    std::ostringstream ostr;
    ostr << "json::get_variant() -> Error. Unknown key '"
        << variant_type.toStdString() << "' in json object.";

    throw std::runtime_error(ostr.str());
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

QJsonObject from_string(const QVariant& variant)
{
    QJsonObject result;
    result[json::variantTypeKey] = json::string_type_name;
    result[json::variantValueKey] = QString::fromStdString(variant.value<std::string>());
    return result;
}

QVariant to_string(const QJsonObject& object)
{
    std::string value = object[json::variantValueKey].toString().toStdString();
    return QVariant::fromValue(value);
}

QJsonObject from_double(const QVariant& variant)
{
    QJsonObject result;
    result[json::variantTypeKey] = json::double_type_name;
    result[json::variantValueKey] = variant.toDouble();
    return result;
}

QVariant to_double(const QJsonObject& object)
{
    return object[json::variantValueKey].toVariant();
}

QJsonObject from_vector_double(const QVariant& variant)
{
    QJsonObject result;
    result[json::variantTypeKey] = json::vector_double_type_name;

    QJsonArray array;
    std::vector<double> data = variant.value<std::vector<double>>();
    std::copy (data.begin(), data.end(), std::back_inserter(array));
    result[json::variantValueKey] = array;
    return result;
}

QVariant to_vector_double(const QJsonObject& object)
{
    auto array = object[json::variantValueKey].toArray();

    std::vector<double> vec;
    for ( auto x : object[json::variantValueKey].toArray())
        vec.push_back(x.toDouble());

    return QVariant::fromValue(vec);
}


}
