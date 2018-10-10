// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONITEMDATA_H
#define JSONITEMDATA_H

#include <QJsonArray>
#include "sessionitemdata.h"

//! Default converter of SessionItemData to/from json object.

class JsonItemData
{
public:
    static const QString roleKey;
    static const QString variantKey;

    QJsonArray get_json(const SessionItemData& data);

    SessionItemData get_data(const QJsonArray& object);

    bool is_valid(const QJsonObject& json);

};

#endif
