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

QJsonArray JsonItemData::get_json(const SessionItemData& data)
{
    QJsonArray result;

    QJsonObject object;
    for (const auto& x : data) {
        object[roleKey] = x.m_role;
        object[variantKey] = json::get_json(x.m_data);
        result.append(object);
    }

    return result;
}

SessionItemData JsonItemData::get_data(const QJsonObject& object)
{
    return {};
}
