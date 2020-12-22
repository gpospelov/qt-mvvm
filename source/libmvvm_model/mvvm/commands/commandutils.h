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

#include "mvvm/interfaces/itembackupstrategy.h"
#include "mvvm/interfaces/itemcopystrategy.h"
#include <memory>

namespace ModelView {

class SessionModel;

//! Creates strategy suitable for item saving/restoring. Restored item will have same identifiers
//! as original.

MVVM_MODEL_EXPORT std::unique_ptr<ItemBackupStrategy>
CreateItemBackupStrategy(const SessionModel* model);

//! Returns strategy for item copying. Identifiers of the copy will be different from identifiers
//! of the original.

MVVM_MODEL_EXPORT std::unique_ptr<ItemCopyStrategy>
CreateItemCopyStrategy(const SessionModel* model);

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDUTILS_H
