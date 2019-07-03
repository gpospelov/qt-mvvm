// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonbackupstrategy.h"
#include "jsonitemconverter.h"
#include "sessionitem.h"
#include <QJsonObject>

using namespace ModelView;

class JsonBackupStrategy::JsonBackupStrategyPrivate
{
public:
    std::unique_ptr<JsonItemConverter> m_converter;
    QJsonObject m_json;
};

JsonBackupStrategy::JsonBackupStrategy(std::unique_ptr<JsonItemConverter> converter)
    : p_impl(std::make_unique<JsonBackupStrategyPrivate>())
{
    p_impl->m_converter = std::move(converter);
}

JsonBackupStrategy::~JsonBackupStrategy() = default;

std::unique_ptr<SessionItem> JsonBackupStrategy::restoreItem() const
{
    return p_impl->m_converter->from_json(p_impl->m_json);
}

void JsonBackupStrategy::saveItem(const SessionItem* item)
{
    p_impl->m_json = p_impl->m_converter->to_json(item);
}
