// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONVARIANT_H
#define JSONVARIANT_H

#include <QJsonObject>
#include <QVariant>

namespace JsonVariant {

const QString variantTypeKey = "type";
const QString variantValueKey = "value";

QJsonObject get_json(const QVariant& variant);

QVariant get_variant(const QJsonObject& object);

}

#endif
