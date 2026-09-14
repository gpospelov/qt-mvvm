// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonvariantconverter.h"
#include "jsonvariantconverter.h"
#include "mvvm/core/variant.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/serialization/jsonutils.h"
#include "mvvm/utils/reallimits.h"
#include <QColor>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <qhashfunctions.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    inline static const QString variantTypeKey = "type";
    inline static const QString variantValueKey = "value";

    class InvalidTypeConverter
    {
    public:

        InvalidTypeConverter() = delete;

        inline static const char *const typeName = "invalid";

        static QJsonObject toJson(const Variant& variant [[maybe_unused]])
        {
            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, QJsonValue() }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object [[maybe_unused]])
        {
            return Variant();
        }
    };

    class BoolConverter
    {
    public:

        BoolConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<bool>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, variant.value<bool>() }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            return Variant::fromValue(object["value"].toBool());
        }
    };

    class IntConverter
    {
    public:

        IntConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<int>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, variant.value<int>() }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            return Variant::fromValue(object["value"].toInt());
        }
    };

    class DoubleConverter
    {
    public:

        DoubleConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<double>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, variant.value<double>() }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            return Variant::fromValue(object["value"].toDouble());
        }
    };

    class VectorOfDoubleConverter
    {
    public:

        VectorOfDoubleConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<std::vector<double>>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            std::vector<double> data = variant.value<std::vector<double>>();
            QJsonArray array;
            std::copy(data.begin(), data.end(), std::back_inserter(array));

            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, array }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            std::vector<double> v;
            for (auto x : object[variantValueKey].toArray()) {
                v.push_back(x.toDouble());
            }

            return Variant::fromValue(v);
        }
    };

    class StringConverter
    {
    public:

        StringConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<std::string>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, QString::fromStdString(variant.value<std::string>()) }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            return Variant::fromValue(object["value"].toString().toStdString());
        }
    };

    class RealLimitsConverter
    {
    private:

        inline static const QString realLimitsTextKey = "text";
        inline static const QString realLimitsMinKey = "min";
        inline static const QString realLimitsMaxKey = "max";

    public:

        RealLimitsConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<ModelView::RealLimits>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            const ModelView::RealLimits limits = variant.value<ModelView::RealLimits>();

            QJsonObject json_data {
                { realLimitsTextKey, QString::fromStdString(ModelView::JsonUtils::ToString(limits)) },
                { realLimitsMinKey, limits.lowerLimit() },
                { realLimitsMaxKey, limits.upperLimit() }
            };

            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, json_data }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            QJsonObject json_data = object[variantValueKey].toObject();

            const std::string text = json_data[realLimitsTextKey].toString().toStdString();
            const double min = json_data[realLimitsMinKey].toDouble();
            const double max = json_data[realLimitsMaxKey].toDouble();

            return Variant::fromValue(ModelView::JsonUtils::CreateLimits(text, min, max));
        }
    };

    class QColorConverter
    {
    public:

        QColorConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<QColor>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            const QColor color = variant.value<QColor>();
            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, color.name(QColor::HexArgb) }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            return Variant::fromValue(QColor(object[variantValueKey].toString()));
        }
    };

    class ComboPropertyConverter
    {
    private:

        inline static const QString comboValuesKey = "values";
        inline static const QString comboSelectionKey = "selections";

    public:

        ComboPropertyConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<ModelView::ComboProperty>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            const ModelView::ComboProperty combo = variant.value<ModelView::ComboProperty>();

            QJsonObject json_data {
                { comboValuesKey, QString::fromStdString(combo.stringOfValues()) },
                { comboSelectionKey, QString::fromStdString(combo.stringOfSelections()) },
            };

            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, json_data }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            QJsonObject json_data = object[variantValueKey].toObject();

            ModelView::ComboProperty combo;
            combo.setStringOfValues(json_data[comboValuesKey].toString().toStdString());
            combo.setStringOfSelections(json_data[comboSelectionKey].toString().toStdString());

            return Variant::fromValue(combo);
        }
    };

    class ExternalPropertyConverter
    {
    private:

        inline static const QString extPropertyTextKey = "text";
        inline static const QString extPropertyColorKey = "color";
        inline static const QString extPropertyIdKey = "identifier";

    public:

        ExternalPropertyConverter() = delete;

        inline static const char *const typeName = QMetaType::fromType<ModelView::ExternalProperty>().name();

        static QJsonObject toJson(const Variant& variant)
        {
            const ModelView::ExternalProperty extprop = variant.value<ModelView::ExternalProperty>();

            QJsonObject json_data {
                { extPropertyTextKey, QString::fromStdString(extprop.text()) },
                { extPropertyColorKey, extprop.color().name(QColor::HexArgb) },
                { extPropertyIdKey, QString::fromStdString(extprop.identifier()) }
            };

            QJsonObject result {
                { variantTypeKey, typeName },
                { variantValueKey, json_data }
            };

            return result;
        }

        static Variant fromJson(const QJsonObject& object)
        {
            QJsonObject json_data = object[variantValueKey].toObject();

            const std::string text = json_data[extPropertyTextKey].toString().toStdString();
            const std::string color = json_data[extPropertyColorKey].toString().toStdString();
            const std::string id = json_data[extPropertyIdKey].toString().toStdString();

            return Variant::fromValue(ModelView::ExternalProperty(text, QColor(QString::fromStdString(color)), id));
        }
    };

    struct Converter
    {
        std::function<QJsonObject(const Variant& variant)> toJson;
        std::function<Variant(const QJsonObject& json)> fromJson;
    };

    inline const std::map<std::string, Converter> converters = []{
        std::map<std::string, Converter> map;
        map.emplace(InvalidTypeConverter::typeName, Converter { InvalidTypeConverter::toJson, InvalidTypeConverter::fromJson });
        map.emplace(BoolConverter::typeName, Converter { BoolConverter::toJson, BoolConverter::fromJson });
        map.emplace(IntConverter::typeName, Converter { IntConverter::toJson, IntConverter::fromJson });
        map.emplace(DoubleConverter::typeName, Converter { DoubleConverter::toJson, DoubleConverter::fromJson });
        map.emplace(StringConverter::typeName, Converter { StringConverter::toJson, StringConverter::fromJson });
        map.emplace(VectorOfDoubleConverter::typeName, Converter { VectorOfDoubleConverter::toJson, VectorOfDoubleConverter::fromJson });
        map.emplace(ComboPropertyConverter::typeName, Converter { ComboPropertyConverter::toJson, ComboPropertyConverter::fromJson });
        map.emplace(QColorConverter::typeName, Converter { QColorConverter::toJson, QColorConverter::fromJson });
        map.emplace(ExternalPropertyConverter::typeName, Converter { ExternalPropertyConverter::toJson, ExternalPropertyConverter::fromJson });
        map.emplace(RealLimitsConverter::typeName, Converter { RealLimitsConverter::toJson, RealLimitsConverter::fromJson });
        return map;
    }();
} // namespace

namespace ModelView
{
    QJsonObject JsonVariantConverter::get_json(const Variant& variant)
    {
        if (!variant.isValid()) {
            return InvalidTypeConverter::toJson(variant);
        }

        auto typeIt = converters.find(variant.typeName());

        if (typeIt == converters.end()) {
            throw std::runtime_error("json::get_json() -> Error: Unknown variant type '" + std::string(variant.typeName()) + "'.");
        }

        const Converter &converter = typeIt->second;
        return converter.toJson(variant);
    }

    Variant JsonVariantConverter::get_variant(const QJsonObject& object)
    {
        auto typeIt = object.find(variantTypeKey);

        if (typeIt == object.end()) {
            throw std::runtime_error("json::get_variant() -> Error: Invalid json object.");
        }

        const std::string typeName = typeIt.value().toString().toStdString();

        if (!object.contains(variantValueKey)) {
            throw std::runtime_error("json::get_variant() -> Error: Invalid json '" + typeName + "' object.");
        }

        auto valueIt = converters.find(typeName);

        if (valueIt == converters.end()) {
            throw std::runtime_error("json::get_variant() -> Error: Unknown variant type '" + typeName + "' in json object.");
        }

        const Converter &converter = valueIt->second;
        return converter.fromJson(object);
    }
} // namespace ModelView
