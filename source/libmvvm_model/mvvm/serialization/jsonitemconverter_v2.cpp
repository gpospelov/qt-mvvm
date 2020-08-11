// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonObject>
#include <mvvm/model/sessionitem.h>
#include <mvvm/serialization/jsonitemconverter_v2.h>

using namespace ModelView;

struct JsonItemConverterV2::JsonItemConverterV2Impl {
    const ItemFactoryInterface* m_factory{nullptr};
    bool m_is_new_id{false};
};

JsonItemConverterV2::JsonItemConverterV2(const ItemFactoryInterface* factory, bool new_id_flag)
    : p_impl(std::make_unique<JsonItemConverterV2Impl>())
{
    p_impl->m_factory = factory;
    p_impl->m_is_new_id = new_id_flag;
}

JsonItemConverterV2::~JsonItemConverterV2() = default;

QJsonObject JsonItemConverterV2::to_json(const SessionItem* /*item*/) const
{
    return {};
}

std::unique_ptr<SessionItem> JsonItemConverterV2::from_json(const QJsonObject& /*json*/) const
{
    return {};
}
