// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonvariantconverter.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/customvariants.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/variant_constants.h"
#include "mvvm/serialization/jsonutils.h"
#include "mvvm/utils/reallimits.h"
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>

using namespace ModelView;

namespace {

const QString variantTypeKey = "type";
const QString variantValueKey = "value";
const QString comboValuesKey = "values";
const QString comboSelectionKey = "selections";
const QString extPropertyTextKey = "text";
const QString extPropertyColorKey = "color";
const QString extPropertyIdKey = "identifier";
const QString realLimitsTextKey = "text";
const QString realLimitsMinKey = "min";
const QString realLimitsMaxKey = "max";

QStringList expected_variant_keys();

QJsonObject from_invalid(const Variant& variant);
Variant to_invalid(const QJsonObject& object);

QJsonObject from_bool(const Variant& variant);
Variant to_bool(const QJsonObject& object);

QJsonObject from_int(const Variant& variant);
Variant to_int(const QJsonObject& object);

QJsonObject from_string(const Variant& variant);
Variant to_string(const QJsonObject& object);

QJsonObject from_double(const Variant& variant);
Variant to_double(const QJsonObject& object);

QJsonObject from_vector_double(const Variant& variant);
Variant to_vector_double(const QJsonObject& object);

QJsonObject from_comboproperty(const Variant& variant);
Variant to_comboproperty(const QJsonObject& object);

QJsonObject from_qcolor(const Variant& variant);
Variant to_qcolor(const QJsonObject& object);

QJsonObject from_extproperty(const Variant& variant);
Variant to_extproperty(const QJsonObject& object);

QJsonObject from_reallimits(const Variant& variant);
Variant to_reallimits(const QJsonObject& object);

} // namespace

JsonVariantConverter::JsonVariantConverter()
{
    m_converters[Constants::invalid_type_name] = {from_invalid, to_invalid};
    m_converters[Constants::bool_type_name] = {from_bool, to_bool};
    m_converters[Constants::int_type_name] = {from_int, to_int};
    m_converters[Constants::string_type_name] = {from_string, to_string};
    m_converters[Constants::double_type_name] = {from_double, to_double};
    m_converters[Constants::vector_double_type_name] = {from_vector_double, to_vector_double};
    m_converters[Constants::comboproperty_type_name] = {from_comboproperty, to_comboproperty};
    m_converters[Constants::qcolor_type_name] = {from_qcolor, to_qcolor};
    m_converters[Constants::extproperty_type_name] = {from_extproperty, to_extproperty};
    m_converters[Constants::reallimits_type_name] = {from_reallimits, to_reallimits};
}

QJsonObject JsonVariantConverter::get_json(const Variant& variant)
{
    const std::string type_name = Utils::VariantName(variant);

    if (m_converters.find(type_name) == m_converters.end())
        throw std::runtime_error("json::get_json() -> Error. Unknown variant type '" + type_name
                                 + "'.");

    return m_converters[type_name].variant_to_json(variant);
}

Variant JsonVariantConverter::get_variant(const QJsonObject& object)
{
    if (!isVariant(object))
        throw std::runtime_error("json::get_variant() -> Error. Invalid json object");

    const auto type_name = object[variantTypeKey].toString().toStdString();
    if (m_converters.find(type_name) == m_converters.end())
        throw std::runtime_error("json::get_variant() -> Error. Unknown variant type '" + type_name
                                 + "' in json object.");

    return m_converters[type_name].json_to_variant(object);
}

//! Returns true if given json object represents variant.

bool JsonVariantConverter::isVariant(const QJsonObject& object) const
{
    static const QStringList expected = expected_variant_keys();
    return object.keys() == expected;
}

namespace {

QStringList expected_variant_keys()
{
    QStringList result = QStringList() << variantTypeKey << variantValueKey;
    std::sort(result.begin(), result.end());
    return result;
}

QJsonObject from_invalid(const Variant& variant)
{
    (void)variant;
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::invalid_type_name);
    result[variantValueKey] = QJsonValue();
    return result;
}

Variant to_invalid(const QJsonObject& object)
{
    (void)object;
    return Variant();
}

QJsonObject from_bool(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::bool_type_name);
    result[variantValueKey] = variant.value<bool>();
    return result;
}

Variant to_bool(const QJsonObject& object)
{
    return object[variantValueKey].toVariant();
}

QJsonObject from_int(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::int_type_name);
    result[variantValueKey] = variant.value<int>();
    return result;
}

Variant to_int(const QJsonObject& object)
{
    // deliberately recreating variant, otherwise it is changing type to Qariant::Double
    return Variant::fromValue(object[variantValueKey].toVariant().value<int>());
}

QJsonObject from_string(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::string_type_name);
    result[variantValueKey] = QString::fromStdString(variant.value<std::string>());
    return result;
}

Variant to_string(const QJsonObject& object)
{
    std::string value = object[variantValueKey].toString().toStdString();
    return Variant::fromValue(value);
}

QJsonObject from_double(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::double_type_name);
    result[variantValueKey] = variant.value<double>();
    return result;
}

Variant to_double(const QJsonObject& object)
{
    // deliberately recreating variant, otherwise it is changing type to qlonglong for
    // numbers like 43.0
    return object[variantValueKey].toVariant().value<double>();
}

// --- std::vector<double> ------

QJsonObject from_vector_double(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::vector_double_type_name);
    QJsonArray array;
    auto data = variant.value<std::vector<double>>();
    std::copy(data.begin(), data.end(), std::back_inserter(array));
    result[variantValueKey] = array;
    return result;
}

Variant to_vector_double(const QJsonObject& object)
{
    std::vector<double> vec;
    for (auto x : object[variantValueKey].toArray())
        vec.push_back(x.toDouble());
    return Variant::fromValue(vec);
}

// --- ComboProperty ------

QJsonObject from_comboproperty(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::comboproperty_type_name);
    auto combo = variant.value<ComboProperty>();
    QJsonObject json_data;
    json_data[comboValuesKey] = QString::fromStdString(combo.stringOfValues());
    json_data[comboSelectionKey] = QString::fromStdString(combo.stringOfSelections());
    result[variantValueKey] = json_data;
    return result;
}

Variant to_comboproperty(const QJsonObject& object)
{
    ComboProperty combo;
    QJsonObject json_data = object[variantValueKey].toObject();
    combo.setStringOfValues(json_data[comboValuesKey].toString().toStdString());
    combo.setStringOfSelections(json_data[comboSelectionKey].toString().toStdString());
    return Variant::fromValue(combo);
}

// --- QColor ------

QJsonObject from_qcolor(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::qcolor_type_name);
    auto color = variant.value<QColor>();
    result[variantValueKey] = color.name(QColor::HexArgb);
    return result;
}

Variant to_qcolor(const QJsonObject& object)
{
    return Variant::fromValue(QColor(object[variantValueKey].toString()));
}

// --- ExternalProperty ------

QJsonObject from_extproperty(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::extproperty_type_name);
    auto extprop = variant.value<ExternalProperty>();
    QJsonObject json_data;
    json_data[extPropertyTextKey] = QString::fromStdString(extprop.text());
    json_data[extPropertyColorKey] = extprop.color().name(QColor::HexArgb);
    json_data[extPropertyIdKey] = QString::fromStdString(extprop.identifier());
    result[variantValueKey] = json_data;
    return result;
}

Variant to_extproperty(const QJsonObject& object)
{
    QJsonObject json_data = object[variantValueKey].toObject();
    const std::string text = json_data[extPropertyTextKey].toString().toStdString();
    const std::string color = json_data[extPropertyColorKey].toString().toStdString();
    const std::string id = json_data[extPropertyIdKey].toString().toStdString();

    return Variant::fromValue(ExternalProperty(text, QColor(QString::fromStdString(color)), id));
}

// --- RealLimits ------

QJsonObject from_reallimits(const Variant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::reallimits_type_name);
    auto limits = variant.value<RealLimits>();
    QJsonObject json_data;

    json_data[realLimitsTextKey] = QString::fromStdString(JsonUtils::ToString(limits));
    json_data[realLimitsMinKey] = limits.lowerLimit();
    json_data[realLimitsMaxKey] = limits.upperLimit();

    result[variantValueKey] = json_data;
    return result;
}

Variant to_reallimits(const QJsonObject& object)
{
    QJsonObject json_data = object[variantValueKey].toObject();
    const std::string text = json_data[realLimitsTextKey].toString().toStdString();
    const double min = json_data[realLimitsMinKey].toDouble();
    const double max = json_data[realLimitsMaxKey].toDouble();

    return Variant::fromValue(JsonUtils::CreateLimits(text, min, max));
}

} // namespace
