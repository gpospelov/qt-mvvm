// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/commands/commandutils.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/serialization/jsonitembackupstrategy.h"
#include "mvvm/serialization/jsonitemcopystrategy.h"

std::unique_ptr<ModelView::ItemBackupStrategy>
ModelView::CreateItemBackupStrategy(const ModelView::SessionModel* model)
{
    assert(model);
    return std::make_unique<JsonItemBackupStrategy>(model->factory());
}

std::unique_ptr<ModelView::ItemCopyStrategy>
ModelView::CreateItemCopyStrategy(const ModelView::SessionModel* model)
{
    assert(model);
    return std::make_unique<JsonItemCopyStrategy>(model->factory());
}
