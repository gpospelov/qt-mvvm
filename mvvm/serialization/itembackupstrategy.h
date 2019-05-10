// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMBACKUPSTRATEGY_H
#define MVVM_ITEMBACKUPSTRATEGY_H

#include "mvvm_global.h"
#include <memory>

namespace ModelView
{

class SessionItem;

//! Interface to backup items within RemoveItemCommand context.

class CORE_EXPORT ItemBackupStrategy
{
public:
    virtual ~ItemBackupStrategy() = default;

    //! Restore item from saved content.
    virtual std::unique_ptr<SessionItem> restoreItem() const = 0;

    //! Save item's content.
    virtual void saveItem(const SessionItem*) = 0;
};

} // namespace ModelView

#endif // MVVM_ITEMBACKUPSTRATEGY_H
