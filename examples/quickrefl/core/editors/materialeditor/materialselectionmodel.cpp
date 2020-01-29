// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialselectionmodel.h"
#include "materialitems.h"
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>

MaterialSelectionModel::MaterialSelectionModel(ModelView::AbstractViewModel* view_model,
                                               QObject* parent)
    : QItemSelectionModel(view_model, parent)
{
}

//! Returns vector of selected materials.

std::vector<MaterialBaseItem*> MaterialSelectionModel::selectedMaterials() const
{
    std::vector<MaterialBaseItem*> result;
    auto selected_items = ModelView::Utils::ParentItemsFromIndex(selectedIndexes());
    std::transform(std::begin(selected_items), std::end(selected_items), std::back_inserter(result),
                   [](auto item) { return dynamic_cast<MaterialBaseItem*>(item); });
    return result;
}
