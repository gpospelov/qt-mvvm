// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H
#define MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H

#include <QString>
#include <memory>
#include <mvvm/serialization/jsonitemdataconverterinterface.h>
#include <vector>

class QJsonObject;

namespace ModelView
{

class JsonVariantConverterInterface;

//! Default converter of SessionItemData to/from json object.

class MVVM_MODEL_EXPORT JsonItemDataConverter : public JsonItemDataConverterInterface
{
public:
    static inline const QString roleKey = "role";
    static inline const QString variantKey = "variant";

    JsonItemDataConverter();
    ~JsonItemDataConverter() override;

    QJsonArray get_json(const SessionItemData& data) override;

    std::unique_ptr<SessionItemData> get_data(const QJsonArray& object) override;
    void from_json(const QJsonArray& object, SessionItemData& data);

    bool is_item_data(const QJsonObject& json);

    void set_role_filter(const std::vector<int>& roles);

private:
    bool role_to_save(int role) const;

    std::unique_ptr<JsonVariantConverterInterface> m_variant_converter;
    //!< List of roles to filter while writing to json.
    std::vector<int> m_roles_to_filter;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H
