// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONTAGINFO_H
#define MVVM_SERIALIZATION_JSONTAGINFO_H

#include <QString>
#include <mvvm/serialization/jsonconverterinterfaces.h>

class QJsonObject;

namespace ModelView
{

//! Default converter between TagInfo and json object.

class CORE_EXPORT JsonTagInfo : public JsonTagInfoInterface
{
public:
    static const QString nameKey;
    static const QString minKey;
    static const QString maxKey;
    static const QString modelsKey;

    QJsonObject to_json(const TagInfo& tag) override;

    TagInfo from_json(const QJsonObject& object) override;

    bool isTagInfo(const QJsonObject& object);
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONTAGINFO_H
