// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H

#include "mvvm/model_export.h"
#include <memory>

class QJsonObject;

namespace ModelView {

class SessionItem;

//! Base class for all converters of SessionItem to/from JSON object.

class MVVM_MODEL_EXPORT JsonItemConverterInterface {
public:
    virtual ~JsonItemConverterInterface() = default;

    //! Converts item to JSON.
    virtual QJsonObject to_json(const SessionItem* item) const = 0;

    //! Creates item from JSON.
    virtual std::unique_ptr<SessionItem> from_json(const QJsonObject&) const = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H
