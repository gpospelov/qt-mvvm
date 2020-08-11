// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCONVERTER_V2_H
#define MVVM_SERIALIZATION_JSONITEMCONVERTER_V2_H

#include <memory>
#include <mvvm/serialization/jsonitemconverterinterface.h>

namespace ModelView
{

class ItemFactoryInterface;

//! Default converter between SessionItem and json object.

class MVVM_MODEL_EXPORT JsonItemConverterV2 : public JsonItemConverterInterface
{
public:
    JsonItemConverterV2(const ItemFactoryInterface* factory, bool new_id_flag = false);
    ~JsonItemConverterV2() override;

    QJsonObject to_json(const SessionItem* item) const override;

    std::unique_ptr<SessionItem> from_json(const QJsonObject& json) const override;

private:
    struct JsonItemConverterV2Impl;
    std::unique_ptr<JsonItemConverterV2Impl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONVERTER_H
