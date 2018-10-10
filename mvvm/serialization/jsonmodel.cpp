// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonmodel.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "itemutils.h"
#include <QJsonObject>
#include <QJsonArray>

const QString JsonModel::modelKey = "model";
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
    if (!item)
        return;

    json[modelKey] = QString::fromStdString(item->modelType());

    QJsonArray itemArray;
    for (auto child : item->children()) {
        QJsonObject child_json;
        write(child, child_json);
        itemArray.append(child_json);
    }
    json[itemsKey] = itemArray;
}

bool JsonModel::is_valid(QJsonObject& object)
{
    static const QStringList expected = QStringList() << itemsKey << modelKey;
    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}

