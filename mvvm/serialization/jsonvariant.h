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

class JsonVariant {
public:

    static const QString variantTypeKey;
    static const QString variantValueKey;

    static const QString invalid_type_name;
    static const QString int_type_name;
    static const QString string_type_name;
    static const QString double_type_name;
    static const QString vector_double_type_name;


    QJsonObject get_json(const QVariant& variant);

    QVariant get_variant(const QJsonObject& object);

};

#endif
