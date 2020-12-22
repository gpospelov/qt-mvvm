// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H

#include "mvvm/model_export.h"
#include <memory>

class QJsonArray;

namespace ModelView {

class SessionItemData;

//! Base class for all converters of SessionItemData to/from JSON object.

class MVVM_MODEL_EXPORT JsonItemDataConverterInterface {
public:
    virtual ~JsonItemDataConverterInterface() = default;

    //! Converts SessionItemData to JSON;
    virtual QJsonArray to_json(const SessionItemData&) = 0;

    //! Converts SessionItemData from JSON;
    virtual void from_json(const QJsonArray& object, SessionItemData& data) = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H
