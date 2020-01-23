// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialselectionmodel.h"
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>

MaterialSelectionModel::MaterialSelectionModel(ModelView::AbstractViewModel* view_model,
                                               QObject* parent)
    : QItemSelectionModel(view_model, parent)
{
}

//! Returns vector of selected materials.

std::vector<ModelView::SessionItem*> MaterialSelectionModel::selectedMaterials() const
{
    return ModelView::Utils::ParentItemsFromIndex(selectedIndexes());
}
