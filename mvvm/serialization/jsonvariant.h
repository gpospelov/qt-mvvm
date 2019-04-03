// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONVARIANT_H
#define JSONVARIANT_H

#include "jsonconverterinterfaces.h"
#include <QJsonObject>
#include <QString>
#include <QVariant>

namespace ModelView
{

class CORE_EXPORT JsonVariant : public JsonVariantInterface
{
public:
    static const QString variantTypeKey;
    static const QString variantValueKey;

    static const std::string invalid_type_name;
    static const std::string int_type_name;
    static const std::string string_type_name;
    static const std::string double_type_name;
    static const std::string vector_double_type_name;
    static const std::string comboproperty_type_name;

    JsonVariant();

    QJsonObject get_json(const QVariant& variant) override;

    QVariant get_variant(const QJsonObject& object) override;

    bool isVariant(const QJsonObject& object) const;

private:
    struct Converters {
        std::function<QJsonObject(const QVariant& variant)> variant_to_json;
        std::function<QVariant(const QJsonObject& json)> json_to_variant;
    };

    std::map<std::string, Converters> m_converters;
};

} // namespace ModelView

#endif
