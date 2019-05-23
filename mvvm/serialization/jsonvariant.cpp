// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonvariant.h"
#include "variant-constants.h"
#include "comboproperty.h"
#include "customvariants.h"
#include "externalproperty.h"
#include "jsonutils.h"
#include "reallimits.h"
#include <QColor>
#include <QJsonArray>
#include <QJsonObject>
#include <sstream>
#include <stdexcept>

using namespace ModelView;

namespace
{

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

QJsonObject from_qcolor(const QVariant& variant);
QVariant to_qcolor(const QJsonObject& object);

QJsonObject from_extproperty(const QVariant& variant);
QVariant to_extproperty(const QJsonObject& object);

QJsonObject from_reallimits(const QVariant& variant);
QVariant to_reallimits(const QJsonObject& object);

} // namespace

JsonVariant::JsonVariant()
{
    m_converters[Constants::invalid_type_name] = {from_invalid, to_invalid};
    m_converters[Constants::int_type_name] = {from_int, to_int};
    m_converters[Constants::string_type_name] = {from_string, to_string};
    m_converters[Constants::double_type_name] = {from_double, to_double};
    m_converters[Constants::vector_double_type_name] = {from_vector_double, to_vector_double};
    m_converters[Constants::comboproperty_type_name] = {from_comboproperty, to_comboproperty};
    m_converters[Constants::qcolor_type_name] = {from_qcolor, to_qcolor};
    m_converters[Constants::extproperty_type_name] = {from_extproperty, to_extproperty};
    m_converters[Constants::reallimits_type_name] = {from_reallimits, to_reallimits};
}

QJsonObject JsonVariant::get_json(const QVariant& variant)
{
    const std::string type_name = variant.isValid() ? variant.typeName() : Constants::invalid_type_name;

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

    const auto type_name = object[variantTypeKey].toString().toStdString();
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
    QStringList result = QStringList() << variantTypeKey << variantValueKey;
    std::sort(result.begin(), result.end());
    return result;
}

QJsonObject from_invalid(const QVariant& variant)
{
    (void)variant;
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::invalid_type_name);
    result[variantValueKey] = QJsonValue();
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
    result[variantTypeKey] = QString::fromStdString(Constants::int_type_name);
    result[variantValueKey] = variant.toInt();
    return result;
}

QVariant to_int(const QJsonObject& object)
{
    // deliberately recreating variant, otherwise it is changing type to QVariant::Double
    return QVariant::fromValue(object[variantValueKey].toVariant().toInt());
}

QJsonObject from_string(const QVariant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::string_type_name);
    result[variantValueKey] = QString::fromStdString(variant.value<std::string>());
    return result;
}

QVariant to_string(const QJsonObject& object)
{
    std::string value = object[variantValueKey].toString().toStdString();
    return QVariant::fromValue(value);
}

QJsonObject from_double(const QVariant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::double_type_name);
    result[variantValueKey] = variant.toDouble();
    return result;
}

QVariant to_double(const QJsonObject& object)
{
    return object[variantValueKey].toVariant();
}

// --- std::vector<double> ------

QJsonObject from_vector_double(const QVariant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::vector_double_type_name);
    QJsonArray array;
    std::vector<double> data = variant.value<std::vector<double>>();
    std::copy(data.begin(), data.end(), std::back_inserter(array));
    result[variantValueKey] = array;
    return result;
}

QVariant to_vector_double(const QJsonObject& object)
{
    std::vector<double> vec;
    for (auto x : object[variantValueKey].toArray())
        vec.push_back(x.toDouble());
    return QVariant::fromValue(vec);
}

// --- ComboProperty ------

QJsonObject from_comboproperty(const QVariant& variant)
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

QVariant to_comboproperty(const QJsonObject& object)
{
    ComboProperty combo;
    QJsonObject json_data = object[variantValueKey].toObject();
    combo.setStringOfValues(json_data[comboValuesKey].toString().toStdString());
    combo.setStringOfSelections(json_data[comboSelectionKey].toString().toStdString());
    return combo.variant();
}

// --- QColor ------

QJsonObject from_qcolor(const QVariant& variant)
{
    QJsonObject result;
    result[variantTypeKey] = QString::fromStdString(Constants::qcolor_type_name);
    auto color = variant.value<QColor>();
    result[variantValueKey] = color.name(QColor::HexArgb);
    return result;
}

QVariant to_qcolor(const QJsonObject& object)
{
    return QVariant::fromValue(QColor(object[variantValueKey].toString()));
}

// --- ExternalProperty ------

QJsonObject from_extproperty(const QVariant& variant)
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

QVariant to_extproperty(const QJsonObject& object)
{
    QJsonObject json_data = object[variantValueKey].toObject();
    const std::string text = json_data[extPropertyTextKey].toString().toStdString();
    const std::string color = json_data[extPropertyColorKey].toString().toStdString();
    const std::string id = json_data[extPropertyIdKey].toString().toStdString();

    return QVariant::fromValue(ExternalProperty(text, QColor(QString::fromStdString(color)), id));
}

// --- RealLimits ------

QJsonObject from_reallimits(const QVariant& variant)
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

QVariant to_reallimits(const QJsonObject& object)
{
    QJsonObject json_data = object[variantValueKey].toObject();
    const std::string text = json_data[realLimitsTextKey].toString().toStdString();
    const double min = json_data[realLimitsMinKey].toDouble();
    const double max = json_data[realLimitsMaxKey].toDouble();

    return QVariant::fromValue(JsonUtils::CreateLimits(text, min, max));
}

} // namespace
