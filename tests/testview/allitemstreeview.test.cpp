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
#include "mvvm/widgets/allitemstreeview.h"

using namespace ModelView;

//! Testing AllItemsTreeView.

class AllItemsTreeViewTest : public ::testing::Test {
};

//! Testing root item change, when one of the item is selected (real life bug).

TEST_F(AllItemsTreeViewTest, initialState)
{
    SessionModel model;
    auto vectorItem = model.insertItem<VectorItem>();

    AllItemsTreeView view;
    view.setRootSessionItem(model.rootItem());
}
