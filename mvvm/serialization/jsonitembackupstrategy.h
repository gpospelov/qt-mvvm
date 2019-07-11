// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_JSONITEMBACKUPSTRATEGY_H
#define MVVM_JSONITEMBACKUPSTRATEGY_H

#include "itembackupstrategy.h"
#include <memory>

namespace ModelView
{

class SessionItem;
class ItemFactoryInterface;

//! Provide backup of SessionItem using json strategy.

class CORE_EXPORT JsonItemBackupStrategy : public ItemBackupStrategy
{
public:
    JsonItemBackupStrategy(const ItemFactoryInterface* item_factory);
    ~JsonItemBackupStrategy() override;

    std::unique_ptr<SessionItem> restoreItem() const override;

    void saveItem(const SessionItem* item) override;

private:
    class JsonItemBackupStrategyPrivate;
    std::unique_ptr<JsonItemBackupStrategyPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_JSONITEMBACKUPSTRATEGY_H
