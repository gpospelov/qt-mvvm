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

//! Converts SessionItemData to/from json object.

namespace JsonItemData
{

const QString roleKey = "role";
const QString variantKey = "variant";

QJsonArray get_json(const SessionItemData& data);

SessionItemData get_data(const QJsonObject& object);

}

#endif
