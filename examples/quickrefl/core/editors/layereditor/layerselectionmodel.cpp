// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layerselectionmodel.h"
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>

LayerSelectionModel::LayerSelectionModel(ModelView::AbstractViewModel* view_model,
                                               QObject* parent)
    : QItemSelectionModel(view_model, parent)
{
}

//! Returns vector of selected materials.

std::vector<ModelView::SessionItem*> LayerSelectionModel::selectedItems() const
{
    return {};
}
