// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMFORMATASSISTANT_H
#define MVVM_SERIALIZATION_JSONITEMFORMATASSISTANT_H

#include "mvvm/serialization/jsonitemconverterinterface.h"
#include <QString>

namespace ModelView {

//! Utility class to determine, whether given JSON object can represent various parts of
//! SessionModel. It is made a class (and not a set of free functions) to allow different formats in
//! the future.

class MVVM_MODEL_EXPORT JsonItemFormatAssistant {
public:
    static inline const QString modelKey = "model";
    static inline const QString itemDataKey = "itemData";
    static inline const QString itemTagsKey = "itemTags";
    static inline const QString defaultTagKey = "defaultTag";
    static inline const QString containerKey = "containers";
    static inline const QString tagInfoKey = "tagInfo";
    static inline const QString itemsKey = "items";
    static inline const QString sessionModelKey = "sessionmodel";
    static inline const QString versionKey = "version";
    static inline const QString roleKey = "role";
    static inline const QString variantKey = "variant";

    bool isSessionItem(const QJsonObject& json) const;
    bool isSessionItemData(const QJsonObject& json) const;
    bool isSessionItemTags(const QJsonObject& json) const;
    bool isSessionItemContainer(const QJsonObject& json) const;
    bool isSessionModel(const QJsonObject& object) const;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMFORMATASSISTANT_H
