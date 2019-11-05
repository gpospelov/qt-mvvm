// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_JSONITEMCONVERTER_H
#define MVVM_JSONITEMCONVERTER_H

#include <mvvm/serialization/jsonconverterinterfaces.h>
#include <QString>
#include <memory>

class QJsonObject;

namespace ModelView
{

class SessionItem;
class SessionItemContainer;
class SessionItemTags;
class ItemFactoryInterface;

//! Default converter between SessionItem and json object.

class CORE_EXPORT JsonItemConverter : public JsonItemConverterInterface
{
public:
    static const QString modelKey;
    static const QString itemDataKey;
    static const QString itemTagsKey;
    static const QString defaultTagKey;
    static const QString containerKey;
    static const QString tagInfoKey;
    static const QString itemsKey;

    JsonItemConverter(const ItemFactoryInterface* factory, bool new_id_flag = false);
    ~JsonItemConverter() override;

    QJsonObject to_json(const SessionItem* item) const override;

    std::unique_ptr<SessionItem> from_json(const QJsonObject& json) const override;

    bool isSessionItem(const QJsonObject& json) const;
    bool isSessionItemTags(const QJsonObject& json) const;
    bool isSessionItemContainer(const QJsonObject& json) const;

private:
    QJsonObject item_to_json(const SessionItem& item) const;
    QJsonObject tags_to_json(const SessionItemTags& tags) const;
    QJsonObject container_to_json(const SessionItemContainer& container) const;

    std::unique_ptr<SessionItem> json_to_item(const QJsonObject& json,
                                              SessionItem* parent = nullptr) const;
    std::unique_ptr<SessionItemTags> json_to_tags(const QJsonObject& json,
                                                  SessionItem* parent) const;

    std::unique_ptr<JsonItemDataInterface> m_itemdata_converter;
    std::unique_ptr<JsonTagInfoInterface> m_taginfo_converter;
    const ItemFactoryInterface* m_factory;
    bool m_generate_new_identifiers;
};

} // namespace ModelView

#endif // MVVM_JSONITEMCONVERTER_H
