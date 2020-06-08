// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dataselectionmodel.h"
#include "datasetitem.h"

#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>

//! The constructor
DataSelectionModel::DataSelectionModel(ModelView::ViewModel* view_model, QObject* parent)
    : QItemSelectionModel(view_model, parent)
{
}

//! Set the selection on a single item
void DataSelectionModel::selectItem(ModelView::SessionItem* item)
{
    selectItems({item});
}

//! Set the selection on a list of items
void DataSelectionModel::selectItems(std::vector<ModelView::SessionItem*> items)
{
    QModelIndexList indexes;
    for (auto item : items)
        indexes << viewModel()->indexOfSessionItem(item);

    if (indexes.empty())
        return;

    clearSelection();

    QItemSelection selection(indexes.front(), indexes.back());
    auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
    select(selection, flags);
}

//! Return the selected items
std::vector<ModelView::SessionItem*> DataSelectionModel::selectedItems() const
{
    return ModelView::Utils::ItemsFromIndex(selectedIndexes());
}

// get the viewmodel
const ModelView::ViewModel* DataSelectionModel::viewModel() const
{
    return static_cast<const ModelView::ViewModel*>(model());
}
