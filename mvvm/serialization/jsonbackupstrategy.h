// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_JSONBACKUPSTRATEGY_H
#define MVVM_JSONBACKUPSTRATEGY_H

#include "itembackupstrategy.h"
#include <memory>

namespace ModelView
{

class SessionItem;
class ItemFactoryInterface;

//! Provide backup of SessionItem using given JsonItemConverter.

class CORE_EXPORT JsonBackupStrategy : public ItemBackupStrategy
{
public:
    JsonBackupStrategy(const ItemFactoryInterface* item_factory);
    ~JsonBackupStrategy();

    std::unique_ptr<SessionItem> restoreItem() const;

    void saveItem(const SessionItem* item);

private:
    class JsonBackupStrategyPrivate;
    std::unique_ptr<JsonBackupStrategyPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_JSONBACKUPSTRATEGY_H
