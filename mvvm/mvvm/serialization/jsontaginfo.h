// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_JSONTAGINFO_H
#define MVVM_JSONTAGINFO_H

#include <mvvm/serialization/jsonconverterinterfaces.h>
#include <QJsonObject>

namespace ModelView {

//! Default converter between TagInfo and json object.

class CORE_EXPORT JsonTagInfo : public JsonTagInfoInterface {
public:
    static const QString nameKey;
    static const QString minKey;
    static const QString maxKey;
    static const QString modelsKey;

    QJsonObject to_json(const TagInfo& tag) override;

    TagInfo from_json(const QJsonObject& object) override;

    bool isTagInfo(const QJsonObject& object);
};

}  // namespace ModelView

#endif // MVVM_JSONTAGINFO_H
