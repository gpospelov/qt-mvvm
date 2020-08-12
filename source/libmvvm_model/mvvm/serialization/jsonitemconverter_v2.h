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

#include <mvvm/serialization/jsonitemconverterinterface.h>

namespace ModelView
{

class ItemFactoryInterface;

//! Converter between SessionItem and JSON object.
//! This is an experimental version with the focus on back compatibility. It tries to reuse
//! item's properties (as they were created by the item constructor), and update from JSON
//! only certain parts.

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
