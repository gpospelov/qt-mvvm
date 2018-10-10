// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONITEMDATA_H
#define JSONITEMDATA_H

#include "jsonconverterinterfaces.h"
#include <QString>
#include <memory>

class QJsonObject;

//! Default converter of SessionItemData to/from json object.

class JsonItemData : public JsonItemDataInterface
{
public:
    static const QString roleKey;
    static const QString variantKey;

    JsonItemData();

    QJsonArray get_json(const SessionItemData& data) override;

    SessionItemData get_data(const QJsonArray& object) override;

    bool is_valid(const QJsonObject& json);

private:
    std::unique_ptr<JsonVariantInterface> m_variant_converter;
};

#endif
