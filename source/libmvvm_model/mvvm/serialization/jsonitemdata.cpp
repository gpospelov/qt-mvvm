// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/serialization/jsonitemdata.h>
#include <mvvm/serialization/jsonvariant.h>
#include <mvvm/model/sessionitemdata.h>
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>

using namespace ModelView;

const QString ModelView::JsonItemData::roleKey = "role";
const QString ModelView::JsonItemData::variantKey = "variant";

namespace {
QJsonValue keyValue(const QJsonValue& parent_value, const QString& key)
{
    const QJsonObject& parent_object = parent_value.toObject();
    return parent_object.value(key);
}
}

JsonItemData::JsonItemData()
    : m_variant_converter(new JsonVariant)
{
}

JsonItemData::~JsonItemData() = default;

QJsonArray JsonItemData::get_json(const SessionItemData& data)
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

std::unique_ptr<SessionItemData> JsonItemData::get_data(const QJsonArray& object)
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

//! Returns true if it is valid DataRole.

bool JsonItemData::is_item_data(const QJsonObject& json)
{
    static const QStringList expected = QStringList() << roleKey << variantKey;
    return json.keys() == expected;
}

//! Sets the list of roles which should be excluded from json.

void JsonItemData::set_role_filter(const std::vector<int>& roles)
{
    m_roles_to_filter = roles;
}

//! Returns true if given role should be saved in json file.

bool JsonItemData::role_to_save(int role) const
{
    bool role_in_list = std::find(m_roles_to_filter.begin(), m_roles_to_filter.end(), role)
            !=m_roles_to_filter.end();
    return !role_in_list;
}
