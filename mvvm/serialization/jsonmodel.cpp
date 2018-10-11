// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonmodel.h"
#include "jsonitemdata.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "itemutils.h"
#include <QSet>
#include <QJsonObject>
#include <QJsonArray>

namespace {
QStringList expected_keys() {
    QStringList result = QStringList() << JsonModel::modelKey << JsonModel::itemDataKey
                                       << JsonModel::itemsKey;
    std::sort(result.begin(), result.end());
    return result;
}
}

const QString JsonModel::modelKey = "model";
const QString JsonModel::itemDataKey = "itemData";
const QString JsonModel::itemsKey = "items";


void JsonModel::write(const SessionModel& model, QJsonObject& json)
{
    json[modelKey] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

//    for(auto item : model.rootItem()->children()) {
//        QJsonObject item_json;

//    }

    json[itemsKey] = itemArray;
}

void JsonModel::write(const SessionItem* item, QJsonObject& json)
{
    JsonItemData item_data_converter;
    if (!item)
        return;

    json[modelKey] = QString::fromStdString(item->modelType());
    json[itemDataKey] = item_data_converter.get_json(item->m_data);

    QJsonArray itemArray;
    for (auto child : item->children()) {
        QJsonObject child_json;
        write(child, child_json);
        itemArray.append(child_json);
    }
    json[itemsKey] = itemArray;
}

#include <QDebug>
bool JsonModel::is_item(QJsonObject& object)
{
    static const QStringList expected = expected_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    if (!object[itemDataKey].isArray())
        return false;

    return true;
}

