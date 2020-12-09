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

#include <functional>
#include <memory>
#include <mvvm/model_export.h>
#include <vector>

class QJsonObject;

namespace ModelView
{

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

//! Flags to define converter behavior on the way from JSON to SessionItem.

enum class ConverterFlags : int {
    NONE = 0,

    USE_JSON_ID = 2,    //!< use serialized ID, otherwise generate new
    COPY_JSON_TAGS = 4, //!< copy tags from serialized content, all existing tags will be rewritten
    COPY_JSON_DATA = 8, //!< copy item's data from serialized content

    //!< exact clone of SessionItem (including item's ID) for backup purposes
    CLONE_MODE = USE_JSON_ID | COPY_JSON_TAGS | COPY_JSON_DATA,

    //!< deep copy of SessionItem (acts like clone with all item's ID regenerated)
    COPY_MODE = COPY_JSON_TAGS | COPY_JSON_DATA,

    //! for loading project from disk (tags and data created by item, updated from JSON)
    PROJECT_MODE = USE_JSON_ID
};

inline ConverterFlags operator&(ConverterFlags x, ConverterFlags y)
{
    return static_cast<ConverterFlags>(static_cast<int>(x) & static_cast<int>(y));
}

inline constexpr ConverterFlags operator|(ConverterFlags x, ConverterFlags y)
{
    return static_cast<ConverterFlags>(static_cast<int>(x) | static_cast<int>(y));
}

inline bool hasFlag(ConverterFlags arg, ConverterFlags flag)
{
    return (arg & flag) != ConverterFlags::NONE;
}

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
    ConverterFlags m_flags = ConverterFlags::NONE;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEM_TYPES_H
