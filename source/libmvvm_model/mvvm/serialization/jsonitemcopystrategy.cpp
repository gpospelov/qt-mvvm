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
#include <mvvm/serialization/jsonitemconverter.h>
#include <mvvm/serialization/jsonitemconverter_v2.h>
#include <mvvm/serialization/jsonitemcopystrategy.h>

using namespace ModelView;

struct JsonItemCopyStrategy::JsonItemCopyStrategyImpl {
    std::unique_ptr<JsonItemConverterInterface> m_converter;
};

JsonItemCopyStrategy::JsonItemCopyStrategy(const ItemFactoryInterface* item_factory)
    : p_impl(std::make_unique<JsonItemCopyStrategyImpl>())
{
    p_impl->m_converter = std::make_unique<JsonItemConverterV2>(item_factory, /*new_id_flag*/ true);
}

JsonItemCopyStrategy::~JsonItemCopyStrategy() = default;

std::unique_ptr<SessionItem> JsonItemCopyStrategy::createCopy(const SessionItem* item) const
{
    auto json = p_impl->m_converter->to_json(item);
    return p_impl->m_converter->from_json(json);
}
