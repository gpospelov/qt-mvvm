// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "jsonbackupstrategy.h"
#include "sessionitem.h"


using namespace ModelView;

class JsonBackupStrategy::JsonBackupStrategyPrivate {
public:
};

JsonBackupStrategy::JsonBackupStrategy()
    : p_impl(std::make_unique<JsonBackupStrategyPrivate>())
{

}

JsonBackupStrategy::~JsonBackupStrategy() = default;

std::unique_ptr<SessionItem> JsonBackupStrategy::restoreItem() const
{
    return {};
}

void JsonBackupStrategy::saveItem(const SessionItem*)
{

}
