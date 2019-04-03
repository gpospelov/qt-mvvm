// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonvariant.h"
#include "comboproperty.h"
#include "customvariants.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <sstream>
#include <stdexcept>

using namespace ModelView;

const QString ModelView::JsonVariant::variantTypeKey = "type";
const QString ModelView::JsonVariant::variantValueKey = "value";

const std::string ModelView::JsonVariant::invalid_type_name = "invalid";
const std::string ModelView::JsonVariant::int_type_name = "int";
const std::string ModelView::JsonVariant::string_type_name = "std::string";
const std::string ModelView::JsonVariant::double_type_name = "double";
const std::string ModelView::JsonVariant::vector_double_type_name = "std::vector<double>";
const std::string ModelView::JsonVariant::comboproperty_type_name = "ComboProperty";

namespace
{

const std::string comboValuesKey = "values";
const std::string comboSelectionKey = "selections";

QStringList expected_variant_keys();

QJsonObject from_invalid(const QVariant& variant);
QVariant to_invalid(const QJsonObject& object);

QJsonObject from_int(const QVariant& variant);
QVariant to_int(const QJsonObject& object);

QJsonObject from_string(const QVariant& variant);
QVariant to_string(const QJsonObject& object);

QJsonObject from_double(const QVariant& variant);
QVariant to_double(const QJsonObject& object);

QJsonObject from_vector_double(const QVariant& variant);
QVariant to_vector_double(const QJsonObject& object);

QJsonObject from_comboproperty(const QVariant& variant);
QVariant to_comboproperty(const QJsonObject& object);

} // namespace

JsonVariant::JsonVariant()
{
    m_converters[invalid_type_name] = {from_invalid, to_invalid};
    m_converters[int_type_name] = {from_int, to_int};
    m_converters[string_type_name] = {from_string, to_string};
    m_converters[double_type_name] = {from_double, to_double};
    m_converters[vector_double_type_name] = {from_vector_double, to_vector_double};
    m_converters[comboproperty_type_name] = {from_comboproperty, to_comboproperty};
}

QJsonObject JsonVariant::get_json(const QVariant& variant)
{
    const std::string type_name = variant.isValid() ? variant.typeName() : invalid_type_name;

    if (m_converters.find(type_name) == m_converters.end())
        throw std::runtime_error("json::get_json() -> Error. Unknown variant type '" + type_name
                                 + "'.");

    return m_converters[type_name].variant_to_json(variant);
}

QVariant JsonVariant::get_variant(const QJsonObject& object)
{
    QVariant result;

    if (!isVariant(object))
        throw std::runtime_error("json::get_variant() -> Error. Invalid json object");

    const auto type_name = object[JsonVariant::variantTypeKey].toString().toStdString();
    if (m_converters.find(type_name) == m_converters.end())
        throw std::runtime_error("json::get_variant() -> Error. Unknown variant type '" + type_name
                                 + "' in json object.");

    return m_converters[type_name].json_to_variant(object);
}

//! Returns true if given json object represents variant.

bool JsonVariant::isVariant(const QJsonObject& object) const
{
    static const QStringList expected = expected_variant_keys();
    return object.keys() == expected ? true : false;
}

namespace
{

QStringList expected_variant_keys()
{
    QStringList result = QStringList()
                         << JsonVariant::variantTypeKey << JsonVariant::variantValueKey;
    std::sort(result.begin(), result.end());
    return result;
}

QJsonObject from_invalid(const QVariant& variant)
{
    (void)variant;
    QJsonObject result;
    result[JsonVariant::variantTypeKey] = QString::fromStdString(JsonVariant::invalid_type_name);
    result[JsonVariant::variantValueKey] = QJsonValue();
    return result;
}

QVariant to_invalid(const QJsonObject& object)
{
    (void)object;
    return QVariant();
}

QJsonObject from_int(const QVariant& variant)
{
    QJsonObject result;
    result[JsonVariant::variantTypeKey] = QString::fromStdString(JsonVariant::int_type_name);
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
    result[JsonVariant::variantTypeKey] = QString::fromStdString(JsonVariant::string_type_name);
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
    result[JsonVariant::variantTypeKey] = QString::fromStdString(JsonVariant::double_type_name);
    result[JsonVariant::variantValueKey] = variant.toDouble();
    return result;
}

QVariant to_double(const QJsonObject& object)
{
    return object[JsonVariant::variantValueKey].toVariant();
}

// --- std::vector<double> ------

QJsonObject from_vector_double(const QVariant& variant)
{
    QJsonObject result;
    result[JsonVariant::variantTypeKey] =
        QString::fromStdString(JsonVariant::vector_double_type_name);

    QJsonArray array;
    std::vector<double> data = variant.value<std::vector<double>>();
    std::copy(data.begin(), data.end(), std::back_inserter(array));
    result[JsonVariant::variantValueKey] = array;
    return result;
}

QVariant to_vector_double(const QJsonObject& object)
{
    std::vector<double> vec;
    for (auto x : object[JsonVariant::variantValueKey].toArray())
        vec.push_back(x.toDouble());
    return QVariant::fromValue(vec);
}

// --- ComboProperty ------

QJsonObject from_comboproperty(const QVariant& variant)
{
    QJsonObject result;
    result[JsonVariant::variantTypeKey] =
        QString::fromStdString(JsonVariant::comboproperty_type_name);

    auto combo = variant.value<ComboProperty>();

    QJsonObject object;
    object[QString::fromStdString(comboValuesKey)] = QString::fromStdString(combo.stringOfValues());
    object[QString::fromStdString(comboSelectionKey)] =
        QString::fromStdString(combo.stringOfSelections());
    result[JsonVariant::variantValueKey] = object;
    return result;
}

QVariant to_comboproperty(const QJsonObject& object)
{
    ComboProperty combo;
    QJsonObject combo_json_data = object[JsonVariant::variantValueKey].toObject();

    auto values = combo_json_data[QString::fromStdString(comboValuesKey)].toString().toStdString();
    combo.setStringOfValues(values);

    auto selections =
        combo_json_data[QString::fromStdString(comboSelectionKey)].toString().toStdString();
    combo.setStringOfSelections(selections);
    return combo.variant();
}

} // namespace
