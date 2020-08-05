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
#include <mvvm/model_export.h>
#include <mvvm/serialization/jsonitemdataconverterinterface.h>
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

class MVVM_MODEL_EXPORT JsonTagInfoConverterInterface
{
public:
    virtual ~JsonTagInfoConverterInterface() = default;

    virtual QJsonObject to_json(const TagInfo&) = 0;

    virtual TagInfo from_json(const QJsonObject&) = 0;
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
