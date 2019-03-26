// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONTAGINFO_H
#define JSONTAGINFO_H

#include "jsonconverterinterfaces.h"
#include <QJsonObject>

namespace ModelView {

class CORE_EXPORT JsonTagInfo : public JsonTagInfoInterface {
public:
    static const QString nameKey;
    static const QString minKey;
    static const QString maxKey;
    static const QString modelsKey;

    QJsonObject get_json(const TagInfo& tag) override;

    TagInfo get_tag_info(const QJsonObject& object) override;

    bool is_tag_info(const QJsonObject& object);
};

}  // namespace ModelView

#endif
