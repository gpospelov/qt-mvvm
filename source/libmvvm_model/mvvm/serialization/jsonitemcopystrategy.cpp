// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/serialization/jsonitemcopystrategy.h>
#include <mvvm/serialization/jsonitemconverter.h>
#include <mvvm/model/sessionitem.h>
#include <QJsonObject>

using namespace ModelView;

struct JsonItemCopyStrategy::JsonItemCopyStrategyImpl
{
    std::unique_ptr<JsonItemConverter> m_converter;
};

JsonItemCopyStrategy::JsonItemCopyStrategy(const ItemFactoryInterface* item_factory)
    : p_impl(std::make_unique<JsonItemCopyStrategyImpl>())
{
    p_impl->m_converter = std::make_unique<JsonItemConverter>(item_factory, /*new_id_flag*/ true);
}

JsonItemCopyStrategy::~JsonItemCopyStrategy() = default;

std::unique_ptr<SessionItem> JsonItemCopyStrategy::createCopy(const SessionItem* item) const
{
    auto json = p_impl->m_converter->to_json(item);
    return p_impl->m_converter->from_json(json);
}
