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

    //! Converts SessionItem to JSON object.
    using item_to_json_t = std::function<QJsonObject(const SessionItem&)>;

    //! Updates existing SessionItem from JSON object.
    using json_to_item_update_t = std::function<void(const QJsonObject&, SessionItem*)>;

    //! Creates new SessionItem from JSON object.
    using json_to_item_t = std::function<std::unique_ptr<SessionItem*>(const QJsonObject&)>;

    item_to_json_t m_item_to_json;
    json_to_item_update_t m_json_to_item_update;
    json_to_item_t m_json_to_item;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEM_TYPES_H
