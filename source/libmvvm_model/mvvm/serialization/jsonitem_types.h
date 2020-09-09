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

struct MVVM_MODEL_EXPORT ConverterContext {
    using item_to_json_t = std::function<QJsonObject(const SessionItem&)>;
    using json_to_item_update_t = std::function<void(const QJsonObject&, SessionItem*)>;
    using json_to_item_t = std::function<std::unique_ptr<SessionItem>(const QJsonObject&)>;

    item_to_json_t m_item_to_json; //! converts SessionItem to JSON object
    json_to_item_update_t m_json_to_item_update;//! updates existing SessionItem from JSON object
    json_to_item_t m_json_to_item; //! creates new SessionItem from JSON object
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEM_TYPES_H
