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
#include <string>
#include <memory>

class QJsonObject;
class QVariant;
class QJsonArray;

namespace ModelView {

class ObsoleteSessionItemTags;
class SessionItemData;
class SessionModel;
class SessionItem;
class SessionItemContainer;
class TagInfo;

//! Base class for all supported converters of QVariant to/from json object

class CORE_EXPORT JsonVariantInterface
{
public:
    virtual ~JsonVariantInterface() = default;

    virtual QJsonObject get_json(const QVariant&) = 0;

    virtual QVariant get_variant(const QJsonObject&) = 0;
};

//! Base class for all converters of TagInfo to/from json object

class CORE_EXPORT JsonTagInfoInterface
{
public:
    virtual ~JsonTagInfoInterface() = default;

    virtual QJsonObject to_json(const TagInfo&) = 0;

    virtual TagInfo from_json(const QJsonObject&) = 0;
};

//! Base class for all converters of SessionItemTags to/from json object

class CORE_EXPORT ObsoleteJsonItemTagsInterface
{
public:
    virtual ~ObsoleteJsonItemTagsInterface() = default;

    virtual QJsonArray get_json(const ObsoleteSessionItemTags&) = 0;

    virtual ObsoleteSessionItemTags get_tags(const QJsonArray&) = 0;
};

//! Base class for all converters of SessionItemData to/from json object

class CORE_EXPORT JsonItemDataInterface
{
public:
    virtual ~JsonItemDataInterface() = default;

    virtual QJsonArray get_json(const SessionItemData&) = 0;

    virtual std::unique_ptr<SessionItemData> get_data(const QJsonArray&) = 0;
};

//! Base class for all converters of SessionItemTag to/from json object

class CORE_EXPORT JsonItemTagInterface
{
public:
    virtual ~JsonItemTagInterface() = default;

    virtual QJsonObject to_json(const SessionItemContainer&) = 0;

    virtual std::unique_ptr<SessionItemContainer> from_json(const QJsonObject&) = 0;
};


//! Base class for all converters of SessionItem to/from json object.

class CORE_EXPORT JsonItemInterface
{
public:
    virtual ~JsonItemInterface() = default;

    virtual void json_to_item(const QJsonObject& json, SessionItem* parent, int row = -1, const std::string& tag={})  const = 0;

    virtual void item_to_json(const SessionItem* item, QJsonObject& json) const = 0;
};

//! Base class for all converters of SessionModel to/from json object.

class CORE_EXPORT JsonModelInterface
{
public:
    virtual ~JsonModelInterface() = default;

    virtual void model_to_json(const SessionModel&, QJsonObject&) const  = 0;

    virtual void json_to_model(const QJsonObject&, SessionModel&) const = 0;

    virtual void json_to_item(const QJsonObject& json, SessionItem* parent, int row = -1, const std::string& tag={})  const = 0;

    virtual void item_to_json(const SessionItem* item, QJsonObject& json) const = 0;
};

}  // namespace ModelView

#endif
