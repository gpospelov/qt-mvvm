// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONCONVERTERINTERFACES_H
#define MVVM_SERIALIZATION_JSONCONVERTERINTERFACES_H

#include <memory>
#include <mvvm/core/export.h>
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

class MVVM_MODEL_EXPORT JsonTagInfoInterface
{
public:
    virtual ~JsonTagInfoInterface() = default;

    virtual QJsonObject to_json(const TagInfo&) = 0;

    virtual TagInfo from_json(const QJsonObject&) = 0;
};

//! Base class for all converters of SessionItemData to/from json object

class MVVM_MODEL_EXPORT JsonItemDataInterface
{
public:
    virtual ~JsonItemDataInterface() = default;

    virtual QJsonArray get_json(const SessionItemData&) = 0;

    virtual std::unique_ptr<SessionItemData> get_data(const QJsonArray&) = 0;
};

//! Base class for all converters of SessionItem to/from json object.

class MVVM_MODEL_EXPORT JsonItemConverterInterface
{
public:
    virtual ~JsonItemConverterInterface() = default;

    virtual QJsonObject to_json(const SessionItem* item) const = 0;

    virtual std::unique_ptr<SessionItem> from_json(const QJsonObject&) const = 0;
};

//! Base class for all converters of SessionModel to/from json object.

class MVVM_MODEL_EXPORT JsonModelConverterInterface
{
public:
    virtual ~JsonModelConverterInterface() = default;

    virtual void model_to_json(const SessionModel&, QJsonObject&) const = 0;

    virtual void json_to_model(const QJsonObject&, SessionModel&) const = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONCONVERTERINTERFACES_H
