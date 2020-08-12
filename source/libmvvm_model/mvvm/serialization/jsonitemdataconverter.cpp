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

JsonItemDataConverter::JsonItemDataConverter() : m_variant_converter(new JsonVariantConverter)
{
    set_role_filter({ItemDataRole::TOOLTIP});
}

JsonItemDataConverter::~JsonItemDataConverter() = default;

QJsonArray JsonItemDataConverter::get_json(const SessionItemData& data)
{
    QJsonArray result;

    for (const auto& x : data) {
        QJsonObject object;
        if (role_to_save(x.m_role)) {
            object[roleKey] = x.m_role;
            object[variantKey] = m_variant_converter->get_json(x.m_data);
            result.append(object);
        }
    }

    return result;
}

std::unique_ptr<SessionItemData> JsonItemDataConverter::get_data(const QJsonArray& object)
{
    auto result = std::make_unique<SessionItemData>();

    for (const auto& x : object) {
        if (!is_item_data(x.toObject()))
            throw std::runtime_error("JsonItemData::get_data() -> Invalid json object.");
        auto role = keyValue(x, roleKey).toInt();
        auto variant = m_variant_converter->get_variant(keyValue(x, variantKey).toObject());
        result->setData(variant, role);
    }

    return result;
}

//! Updates existing data with JSON content.

void JsonItemDataConverter::from_json(const QJsonArray& object, SessionItemData& data)
{
    auto persistent_data = get_data(object);

    for (auto role : data.roles())
        if (persistent_data->hasData(role))
            data.setData(persistent_data->data(role), role);
}

//! Returns true if it is valid DataRole.

bool JsonItemDataConverter::is_item_data(const QJsonObject& json)
{
    static const QStringList expected = QStringList() << roleKey << variantKey;
    return json.keys() == expected;
}

//! Sets the list of roles which should be excluded from json.
//! It is used, for example, to not to serialize tooltips. Tooltips are set by the GUI, no need
//! to read older tooltips.

void JsonItemDataConverter::set_role_filter(const std::vector<int>& roles)
{
    m_roles_to_filter = roles;
}

//! Returns true if given role should be saved in json file.

bool JsonItemDataConverter::role_to_save(int role) const
{
    bool role_in_list = std::find(m_roles_to_filter.begin(), m_roles_to_filter.end(), role)
                        != m_roles_to_filter.end();
    return !role_in_list;
}
