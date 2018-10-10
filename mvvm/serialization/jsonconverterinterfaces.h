// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONCONVERTERINTERFACES_H
#define JSONCONVERTERINTERFACES_H

class SessionItemData;
class QJsonArray;

//! Base class for all converters of SessionItemData to/from json object

class JsonItemDataInterface
{
public:
    virtual ~JsonItemDataInterface() = default;

    virtual QJsonArray get_json(const SessionItemData&) = 0;

    virtual SessionItemData get_data(const QJsonArray&) = 0;
};

//! Base class for all supported converters of Qvariant to/from json object

class QJsonObject;
class QVariant;

class JsonVariantInterface
{
public:
    virtual ~JsonVariantInterface() = default;

    virtual QJsonObject get_json(const QVariant&) = 0;

    virtual QVariant get_variant(const QJsonObject&) = 0;
};

#endif
