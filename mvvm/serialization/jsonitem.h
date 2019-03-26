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
class JsonItemDataInterface;
class ObsoleteJsonItemTagsInterface;

class CORE_EXPORT JsonItem : public JsonItemInterface
{
public:
    static const QString modelKey;
    static const QString parentTagKey;
    static const QString itemDataKey;
    static const QString itemTagsKey;
    static const QString itemsKey;

    JsonItem();
    ~JsonItem() override;

    //! Constructs SessionItem tree from json.
    void json_to_item(const QJsonObject& json, SessionItem* parent, int row = -1, const std::string& tag={}) const override;

    //! Writes SessionItem tree to json.
    void item_to_json(const SessionItem* item, QJsonObject& json) const override;

    //! Returns true if given json object represents SessionItem tree.
    bool is_item(const QJsonObject& object) const;

private:
    std::unique_ptr<JsonItemDataInterface> m_itemdata_converter;
    std::unique_ptr<ObsoleteJsonItemTagsInterface> m_itemtags_converter;
};

}  // namespace ModelView

#endif
