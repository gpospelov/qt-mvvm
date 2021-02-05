// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/allitemstreeview.h"

#include "google_test.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/standarditemincludes.h"
#include "mvvm/viewmodel/viewmodel.h"
#include "mvvm/widgets/allitemstreeview.h"
#include <QItemSelectionModel>
#include <QTreeView>

using namespace ModelView;

//! Testing AllItemsTreeView.

class AllItemsTreeViewTest : public ::testing::Test {
};

//! Testing root item change, when one of the item is selected (real life bug).

TEST_F(AllItemsTreeViewTest, initialState)
{
    // setting up model and viewmodel
    SessionModel model;
    auto vectorItem = model.insertItem<VectorItem>();
    auto xItem = vectorItem->getItem(VectorItem::P_X);
    AllItemsTreeView view(&model);
    view.setRootSessionItem(vectorItem);

    // access to internals
    auto selectionModel = view.treeView()->selectionModel();
    auto viewModel = view.viewModel();

    // selecting item in a widget
    selectionModel->select(viewModel->indexOfSessionItem(xItem).front(),
                           QItemSelectionModel::SelectCurrent);

    // Changing root item. The problem was chain of signals (AboutToReset, RowIserted), which
    // was triggering persistentModelIndex.
    ASSERT_NO_FATAL_FAILURE(view.setRootSessionItem(model.rootItem()));
}
