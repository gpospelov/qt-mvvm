// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCONVERTER_H
#define MVVM_SERIALIZATION_JSONITEMCONVERTER_H

#include <QString>
#include <memory>
#include <mvvm/serialization/jsonitemconverterinterface.h>

class QJsonObject;

namespace ModelView
{

class SessionItemContainer;
class SessionItemTags;
class ItemFactoryInterface;
class JsonItemDataConverterInterface;
class JsonTagInfoConverterInterface;

//! Default converter between SessionItem and json object.

class MVVM_MODEL_EXPORT JsonItemConverter : public JsonItemConverterInterface
{
public:
    static inline const QString modelKey = "model";
    static inline const QString itemDataKey = "itemData";
    static inline const QString itemTagsKey = "itemTags";
    static inline const QString defaultTagKey = "defaultTag";
    static inline const QString containerKey= "containers";
    static inline const QString tagInfoKey = "tagInfo";
    static inline const QString itemsKey = "items";

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

    std::unique_ptr<JsonItemDataConverterInterface> m_itemdata_converter;
    std::unique_ptr<JsonTagInfoConverterInterface> m_taginfo_converter;
    const ItemFactoryInterface* m_factory;
    bool m_generate_new_identifiers;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONVERTER_H
