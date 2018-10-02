// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modeljson.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "itemutils.h"
#include <QJsonObject>
#include <QJsonArray>


void ModelJson::write(const SessionModel& model, QJsonObject& json)
{
    json[modelKey.c_str()] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

//    for(auto item : model.rootItem()->children()) {
//        QJsonObject item_json;

//    }

    json[itemsKey.c_str()] = itemArray;
}

void ModelJson::write(const SessionItem* item, QJsonObject& json)
{
    if (!item)
        return;

    json[modelKey.c_str()] = QString::fromStdString(item->modelType());

    QJsonArray itemArray;
    for (auto child : item->children()) {
        QJsonObject child_json;
        write(child, child_json);
        itemArray.append(child_json);
    }
    json[itemsKey.c_str()] = itemArray;
}

