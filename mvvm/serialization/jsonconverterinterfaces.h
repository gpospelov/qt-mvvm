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

#include "global.h"

class QJsonObject;
class QVariant;
class QJsonArray;

namespace ModelView {

class SessionItemTags;
class SessionItemData;
class SessionModel;
class SessionItem;

//! Base class for all supported converters of QVariant to/from json object

class CORE_EXPORT JsonVariantInterface
{
public:
    virtual ~JsonVariantInterface() = default;

    virtual QJsonObject get_json(const QVariant&) = 0;

    virtual QVariant get_variant(const QJsonObject&) = 0;
};

//! Base class for all converters of SessionItemTags to/from json object

class CORE_EXPORT JsonItemTagsInterface
{
public:
    virtual ~JsonItemTagsInterface() = default;

    virtual QJsonArray get_json(const SessionItemTags&) = 0;

    virtual SessionItemTags get_tags(const QJsonArray&) = 0;
};

//! Base class for all converters of SessionItemData to/from json object

class CORE_EXPORT JsonItemDataInterface
{
public:
    virtual ~JsonItemDataInterface() = default;

    virtual QJsonArray get_json(const SessionItemData&) = 0;

    virtual SessionItemData get_data(const QJsonArray&) = 0;
};

//! Base class for all converters of SessionItem to/from json object.

class CORE_EXPORT JsonItemInterface
{
public:
    virtual ~JsonItemInterface() = default;

    virtual void json_to_item(const QJsonObject& json, SessionItem* parent, int row = -1)  const = 0;

    virtual void item_to_json(const SessionItem* item, QJsonObject& json) const = 0;

    virtual bool is_item(const QJsonObject& object) const = 0;
};

//! Base class for all converters of SessionModel to/from json object.

class CORE_EXPORT JsonModelInterface
{
public:
    virtual ~JsonModelInterface() = default;

    virtual void model_to_json(const SessionModel&, QJsonObject&) const  = 0;

    virtual void json_to_model(const QJsonObject&, SessionModel&) const = 0;

    virtual void json_to_item(const QJsonObject& json, SessionItem* parent, int row = -1)  const = 0;

    virtual void item_to_json(const SessionItem* item, QJsonObject& json) const = 0;
};

}  // namespace ModelView

#endif
