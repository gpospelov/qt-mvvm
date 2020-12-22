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
//! Collection of custom types involved into SessionItem and JSON mutual convertion.

#include "mvvm/model_export.h"
#include <functional>
#include <memory>
#include <vector>

class QJsonObject;

namespace ModelView {

class SessionItem;
class ItemFactoryInterface;

//! Provides necessary callbacks to convert SessionItem to JSON and back.

struct MVVM_MODEL_EXPORT ConverterCallbacks {
    using create_json_t = std::function<QJsonObject(const SessionItem&)>;
    using create_item_t = std::function<std::unique_ptr<SessionItem>(const QJsonObject&)>;
    using update_item_t = std::function<void(const QJsonObject&, SessionItem*)>;

    create_json_t m_create_json; //! creates JSON object from session item
    create_item_t m_create_item; //! creates new SessionItem from JSON object
    update_item_t m_update_item; //! updates existing SessionItem from JSON object
};

//! Flags to define converter behavior on the way from SessionItem to JSON and back.

enum class ConverterMode {
    none,   //!< undefined converter mode
    clone,  //!< full deep copying with item identifiers preserved
    copy,   //!< full deep copying with item identifiers regenerated
    project //!< selective copying for saving/loading the project (tags and data created by item,
            //!< updated from JSON)
};

//! Returns true if given mode requires ID regeneration instead of using the one stored in JSON.
inline bool isRegenerateIdWhenBackFromJson(ConverterMode mode)
{
    return mode == ConverterMode::copy;
}

//! Returns true if item content should be reconstructed from JSON
inline bool isRebuildItemDataAndTagFromJson(ConverterMode mode)
{
    return mode != ConverterMode::project;
}

//! Collection of input paramters for SessionItemConverter

struct MVVM_MODEL_EXPORT ConverterContext {
    const ItemFactoryInterface* m_factory{nullptr};
    ConverterMode m_mode = ConverterMode::none;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEM_TYPES_H
