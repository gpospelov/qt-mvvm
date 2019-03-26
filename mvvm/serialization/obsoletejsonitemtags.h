// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONITEMTAGS_H
#define JSONITEMTAGS_H

#include "jsonconverterinterfaces.h"
#include <QString>
#include <memory>
#include <vector>

class QJsonObject;

namespace ModelView {

//! Default converter of SessionItemTags to/from json object.

class CORE_EXPORT ObsoleteJsonItemTags : public ObsoleteJsonItemTagsInterface
{
public:
    static const QString nameKey;
    static const QString minKey;
    static const QString maxKey;
    static const QString countKey;
    static const QString modelsKey;

    ObsoleteJsonItemTags();
    ~ObsoleteJsonItemTags() override;

    QJsonArray get_json(const ObsoleteSessionItemTags& itemTags) override;

    ObsoleteSessionItemTags get_tags(const QJsonArray& object) override;

    bool is_item_tag(const QJsonObject& object);
};

}  // namespace ModelView

#endif // JSONITEMTAGS_H
