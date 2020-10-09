// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonArray>
#include <QJsonObject>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/serialization/jsonitemdataconverter.h>
#include <mvvm/serialization/jsonvariantconverter.h>
#include <mvvm/serialization/jsonitemformatassistant.h>
#include <set>
#include <stdexcept>

using namespace ModelView;

namespace
{
QJsonValue keyValue(const QJsonValue& parent_value, const QString& key)
{
    const QJsonObject& parent_object = parent_value.toObject();
    return parent_object.value(key);
}
} // namespace

JsonItemDataConverter::JsonItemDataConverter(accept_strategy_t to_json_accept,
                                             accept_strategy_t from_json_accept)
    : m_to_json_accept(to_json_accept), m_from_json_accept(from_json_accept),
      m_variant_converter(std::make_unique<JsonVariantConverter>())
{
}

JsonItemDataConverter::~JsonItemDataConverter() = default;

QJsonArray JsonItemDataConverter::to_json(const SessionItemData& data)
{
    QJsonArray result;

    for (const auto& x : data) {
        QJsonObject object;
        if (isRoleToJson(x.m_role)) {
            object[JsonItemFormatAssistant::roleKey] = x.m_role;
            object[JsonItemFormatAssistant::variantKey] = m_variant_converter->get_json(x.m_data);
            result.append(object);
        }
    }

    return result;
}

//! Updates existing data with JSON content.

void JsonItemDataConverter::from_json(const QJsonArray& object, SessionItemData& data)
{
    auto persistent_data = std::make_unique<SessionItemData>();

    for (const auto& x : object) {
        if (!is_item_data(x.toObject()))
            throw std::runtime_error("JsonItemData::get_data() -> Invalid json object.");
        auto role = keyValue(x, JsonItemFormatAssistant::roleKey).toInt();
        auto variant = m_variant_converter->get_variant(keyValue(x, JsonItemFormatAssistant::variantKey).toObject());
        if (isRoleFromJson(role))
            persistent_data->setData(variant, role);
    }

    auto runtime_roles = data.roles();
    auto persistent_roles = persistent_data->roles();

    std::set<int> roles(runtime_roles.begin(), runtime_roles.end());
    roles.insert(persistent_roles.begin(), persistent_roles.end());

    for (auto role : roles) {
        // all roles existing in `persistent` will be taken from there
        if (persistent_data->hasData(role))
            data.setData(persistent_data->data(role), role);
    }
}

//! Returns true if it is valid DataRole.

bool JsonItemDataConverter::is_item_data(const QJsonObject& json)
{
    static const QStringList expected = QStringList() << JsonItemFormatAssistant::roleKey << JsonItemFormatAssistant::variantKey;
    return json.keys() == expected;
}

//! Returns true if given role should be saved in json object.

bool JsonItemDataConverter::isRoleToJson(int role) const
{
    return m_to_json_accept ? m_to_json_accept(role) : true;
}

//! Returns true if given role should be parsed from json object.

bool JsonItemDataConverter::isRoleFromJson(int role) const
{
    return m_from_json_accept ? m_from_json_accept(role) : true;
}
