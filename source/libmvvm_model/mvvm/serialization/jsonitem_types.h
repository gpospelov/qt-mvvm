// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEM_TYPES_H
#define MVVM_SERIALIZATION_JSONITEM_TYPES_H

//! @file jsonitem_types.h
//! Collection of custom types involved into SessionItem <--> JSON convertion.

#include <functional>
#include <memory>
#include <mvvm/model_export.h>
#include <vector>

class QJsonObject;

namespace ModelView
{

class SessionItem;

//! Provides necessary callbacks to convert SessionItem to JSON and back.

struct MVVM_MODEL_EXPORT ConverterCallbacks {
    using create_json_t = std::function<QJsonObject(const SessionItem&)>;
    using update_item_t = std::function<void(const QJsonObject&, SessionItem*)>;
    using create_item_t = std::function<std::unique_ptr<SessionItem>(const QJsonObject&)>;

    create_json_t m_create_json; //! creates JSON object from session item
    update_item_t m_update_item; //! updates existing SessionItem from JSON object
    create_item_t m_create_item; //! creates new SessionItem from JSON object
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEM_TYPES_H
