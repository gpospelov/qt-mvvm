// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONITEM_H
#define JSONITEM_H

#include "jsonconverterinterfaces.h"
#include <QString>
#include <memory>

class QJsonObject;

namespace ModelView {

class SessionItem;
class SessionItemTags;
class SessionItemContainer;

class CORE_EXPORT JsonItem : public JsonItemInterface
{
public:
    static const QString modelKey;
    static const QString itemDataKey;
    static const QString itemTagsKey;
    static const QString defaultTagKey;
    static const QString containerKey;
    static const QString tagInfoKey;
    static const QString itemsKey;

    JsonItem();
    ~JsonItem();

    QJsonObject to_json(const SessionItem* item)  const override;

    std::unique_ptr<SessionItem> from_json(const QJsonObject& json) const override;

private:
    QJsonObject tags_to_json(const SessionItemTags& tags) const;
    QJsonObject container_to_json(const SessionItemContainer& container) const;

    std::unique_ptr<JsonItemDataInterface> m_itemdata_converter;
    std::unique_ptr<JsonTagInfoInterface> m_taginfo_converter;
};

}  // namespace ModelView

#endif // JSONITEM_H
