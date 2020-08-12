// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H
#define MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H

#include <functional>
#include <memory>
#include <mvvm/model_export.h>

class QJsonObject;

namespace ModelView
{

class SessionItem;
class SessionItemContainer;

class MVVM_MODEL_EXPORT JsonItemContainerConverter
{
public:
    using item_to_json_t = std::function<QJsonObject(const SessionItem&)>;
    using json_to_item_update_t = std::function<void(const QJsonObject& json, SessionItem* item)>;
    using json_to_item_t = std::function<std::unique_ptr<SessionItem*>(const QJsonObject& json)>;

    JsonItemContainerConverter();
    ~JsonItemContainerConverter();

    QJsonObject to_json(const SessionItemContainer& container);

    void from_json(const QJsonObject& json, SessionItemContainer& container);

private:
    struct JsonItemContainerConverterImpl;
    std::unique_ptr<JsonItemContainerConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H
