// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COMMANDUTILS_H
#define MVVM_COMMANDS_COMMANDUTILS_H

//! @file commandutils.h
//! Collection of various utility functions for command service.

#include <memory>
#include <mvvm/interfaces/itembackupstrategy.h>
#include <mvvm/interfaces/itemcopystrategy.h>

namespace ModelView
{

class SessionModel;

//! Creates default strategy for item backup.
std::unique_ptr<ItemBackupStrategy> CreateItemBackupStrategy(const SessionModel* model);

//! Creates default strategy for item copying.
std::unique_ptr<ItemCopyStrategy> CreateItemCopyStrategy(const SessionModel* model);

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDUTILS_H
