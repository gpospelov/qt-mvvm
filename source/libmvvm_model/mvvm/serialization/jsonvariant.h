// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONVARIANT_H
#define MVVM_SERIALIZATION_JSONVARIANT_H

#include <functional>
#include <map>
#include <mvvm/serialization/jsonvariantinterface.h>

class QJsonObject;
class QJsonVariant;

namespace ModelView
{

class MVVM_MODEL_EXPORT JsonVariant : public JsonVariantInterface
{
public:
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

#endif // MVVM_SERIALIZATION_JSONVARIANT_H
