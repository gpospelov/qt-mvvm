// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMDATA_H
#define MVVM_SERIALIZATION_JSONITEMDATA_H

#include <mvvm/serialization/jsonconverterinterfaces.h>
#include <QString>
#include <memory>
#include <vector>

class QJsonObject;

namespace ModelView {

class JsonVariantInterface;

//! Default converter of SessionItemData to/from json object.

class CORE_EXPORT JsonItemData : public JsonItemDataInterface
{
public:
    static const QString roleKey;
    static const QString variantKey;

    JsonItemData();
    ~JsonItemData() override;

    QJsonArray get_json(const SessionItemData& data) override;

    std::unique_ptr<SessionItemData> get_data(const QJsonArray& object) override;

    bool is_item_data(const QJsonObject& json);

    void set_role_filter(const std::vector<int>& roles);

    bool role_to_save(int role) const;

private:
    std::unique_ptr<JsonVariantInterface> m_variant_converter;
    //!< List of roles to filter while writing to json.
    std::vector<int> m_roles_to_filter;
};

}  // namespace ModelView

#endif  // MVVM_SERIALIZATION_JSONITEMDATA_H
