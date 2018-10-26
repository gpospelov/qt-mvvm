// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonvariant.h"
#include "customvariants.h"
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>
#include <sstream>

using namespace ModelView;

const QString JsonVariant::variantTypeKey = "type";
const QString JsonVariant::variantValueKey = "value";
const QString JsonVariant::invalid_type_name = "invalid";
const QString JsonVariant::int_type_name = "int";
const QString JsonVariant::string_type_name = "std::string";
const QString JsonVariant::double_type_name = "double";
const QString JsonVariant::vector_double_type_name = "std::vector<double>";


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

QJsonObject JsonVariant::get_json(const QVariant& variant)
{
    QJsonObject result;
    const QString type_name = variant.typeName();

    if (!variant.isValid())
        result = from_invalid();

    else if (type_name == JsonVariant::int_type_name)
        result = from_int(variant);

    else if (type_name == JsonVariant::string_type_name)
        result = from_string(variant);

    else if (type_name == JsonVariant::double_type_name)
        result = from_double(variant);

    else if (type_name == JsonVariant::vector_double_type_name)
        result = from_vector_double(variant);

    else
        throw std::runtime_error("json::get_json() -> Error. Unknown variant type '" +
                             std::string(variant.typeName())+"'.");

    return result;
}

QVariant JsonVariant::get_variant(const QJsonObject& object)
{
    QVariant result;

    if (!is_valid(object))
        throw std::runtime_error("json::get_variant() -> Error. Invalid json object");

    const auto variant_type = object[JsonVariant::variantTypeKey].toString();

    if (variant_type == JsonVariant::invalid_type_name)
        result = QVariant();

    else if(variant_type == JsonVariant::int_type_name)
        result = to_int(object);

    else if(variant_type == JsonVariant::string_type_name)
        result = to_string(object);

    else if(variant_type == JsonVariant::double_type_name)
        result = to_double(object);

    else if(variant_type == JsonVariant::vector_double_type_name)
        result = to_vector_double(object);

    else {
        std::ostringstream ostr;
        ostr << "json::get_variant() -> Error. Unknown key '"
            << variant_type.toStdString() << "' in json object.";
        throw std::runtime_error(ostr.str());
    }

    return result;
}

namespace {

bool is_valid(const QJsonObject& json)
{
    static const QStringList expected = QStringList() << JsonVariant::variantTypeKey << JsonVariant::variantValueKey;
    return json.keys() == expected;
}

QJsonObject from_invalid()
{
    QJsonObject result;
    result[JsonVariant::variantTypeKey] = JsonVariant::invalid_type_name;
    result[JsonVariant::variantValueKey] = QJsonValue();
    return result;
}

QJsonObject from_int(const QVariant& variant)
{
    QJsonObject result;
    result[JsonVariant::variantTypeKey] = JsonVariant::int_type_name;
    result[JsonVariant::variantValueKey] = variant.toInt();
    return result;
}

QVariant to_int(const QJsonObject& object)
{
    return object[JsonVariant::variantValueKey].toVariant();
}

QJsonObject from_string(const QVariant& variant)
{
    QJsonObject result;
    result[JsonVariant::variantTypeKey] = JsonVariant::string_type_name;
    result[JsonVariant::variantValueKey] = QString::fromStdString(variant.value<std::string>());
    return result;
}

QVariant to_string(const QJsonObject& object)
{
    std::string value = object[JsonVariant::variantValueKey].toString().toStdString();
    return QVariant::fromValue(value);
}

QJsonObject from_double(const QVariant& variant)
{
    QJsonObject result;
    result[JsonVariant::variantTypeKey] = JsonVariant::double_type_name;
    result[JsonVariant::variantValueKey] = variant.toDouble();
    return result;
}

QVariant to_double(const QJsonObject& object)
{
    return object[JsonVariant::variantValueKey].toVariant();
}

QJsonObject from_vector_double(const QVariant& variant)
{
    QJsonObject result;
    result[JsonVariant::variantTypeKey] = JsonVariant::vector_double_type_name;

    QJsonArray array;
    std::vector<double> data = variant.value<std::vector<double>>();
    std::copy (data.begin(), data.end(), std::back_inserter(array));
    result[JsonVariant::variantValueKey] = array;
    return result;
}

QVariant to_vector_double(const QJsonObject& object)
{
    auto array = object[JsonVariant::variantValueKey].toArray();

    std::vector<double> vec;
    for ( auto x : object[JsonVariant::variantValueKey].toArray())
        vec.push_back(x.toDouble());

    return QVariant::fromValue(vec);
}


}
