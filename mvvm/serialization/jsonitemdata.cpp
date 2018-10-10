// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonitemdata.h"
#include "jsonvariant.h"
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>


const QString JsonItemData::roleKey = "role";
const QString JsonItemData::variantKey = "variant";


QJsonArray JsonItemData::get_json(const SessionItemData& data)
{
    QJsonArray result;

    QJsonObject object;
    for (const auto& x : data) {
        object[roleKey] = x.m_role;
        object[variantKey] = JsonVariant::get_json(x.m_data);
        result.append(object);
    }

    return result;
}

SessionItemData JsonItemData::get_data(const QJsonArray& object)
{
    SessionItemData result;

    for ( const auto& x : object) {
        if (!is_valid(x.toObject()))
            throw std::runtime_error("JsonItemData::get_data() -> Invalid");
        auto role = x[roleKey].toInt();
        auto variant = JsonVariant::get_variant(x[variantKey].toObject());
        result.setData(variant, role);
    }

    return result;
}

//! Returns true if it is valid DataRole
bool JsonItemData::is_valid(const QJsonObject& json)
{
    static const QStringList expected = QStringList() << roleKey << variantKey;
    return json.keys() == expected ? true : false;
}
