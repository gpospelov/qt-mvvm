// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_JSONCONVERTERINTERFACES_H
#define MVVM_JSONCONVERTERINTERFACES_H

#include "mvvm_export.h"
#include <memory>
#include <string>

class QJsonObject;
class QVariant;
class QJsonArray;

namespace ModelView
{

class SessionItemData;
class SessionModel;
class SessionItem;
class SessionItemContainer;
class TagInfo;

//! Base class for all converters of TagInfo to/from json object

class CORE_EXPORT JsonTagInfoInterface
{
public:
    virtual ~JsonTagInfoInterface() = default;

    virtual QJsonObject to_json(const TagInfo&) = 0;

    virtual TagInfo from_json(const QJsonObject&) = 0;
};

//! Base class for all converters of SessionItemData to/from json object

class CORE_EXPORT JsonItemDataInterface
{
public:
    virtual ~JsonItemDataInterface() = default;

    virtual QJsonArray get_json(const SessionItemData&) = 0;

    virtual std::unique_ptr<SessionItemData> get_data(const QJsonArray&) = 0;
};

//! Base class for all converters of SessionItem to/from json object.

class CORE_EXPORT JsonItemConverterInterface
{
public:
    virtual ~JsonItemConverterInterface() = default;

    virtual QJsonObject to_json(const SessionItem* item) const = 0;

    virtual std::unique_ptr<SessionItem> from_json(const QJsonObject&) const = 0;
};

//! Base class for all converters of SessionModel to/from json object.

class CORE_EXPORT JsonModelInterface
{
public:
    virtual ~JsonModelInterface() = default;

    virtual void model_to_json(const SessionModel&, QJsonObject&) const = 0;

    virtual void json_to_model(const QJsonObject&, SessionModel&) const = 0;
};

} // namespace ModelView

#endif // MVVM_JSONCONVERTERINTERFACES_H
