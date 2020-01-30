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

LayerSelectionModel::LayerSelectionModel(ModelView::AbstractViewModel* view_model, QObject* parent)
    : QItemSelectionModel(view_model, parent)
{
}

//! Selects whole row corresponding to given item.

void LayerSelectionModel::selectItem(ModelView::SessionItem* item)
{
    const QModelIndexList index_list = viewModel()->indexOfSessionItem(item);
    if (index_list.empty())
        return;

    const QModelIndex& id = index_list.front(); // assuming one-to-one index/item correspondence
    auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
    select(id, flags);
    setCurrentIndex(id, flags);
}

//! Returns vector of selected layers or multilayers.
//! We assume, that there is a single line selection mode switched on, and that
//! the first column always contains either MultiLayerItem or LayerItem.

std::vector<ModelView::SessionItem*> LayerSelectionModel::selectedItems() const
{
    const QModelIndexList& selection = selectedRows();
    if (selection.empty())
        return {};

    std::vector<ModelView::SessionItem*> result;
    for (const auto& index : selection)
        if (auto item = viewModel()->sessionItemFromIndex(index); item)
            result.push_back(item);

    return result;
}

const ModelView::AbstractViewModel* LayerSelectionModel::viewModel() const
{
    return dynamic_cast<const ModelView::AbstractViewModel*>(model());
}
