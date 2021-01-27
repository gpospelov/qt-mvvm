// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/propertyviewmodel.h"

#include "google_test.h"
#include "toyitems.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/standarditems/vectoritem.h"

using namespace ModelView;

//! Tests for PropertyViewModel class.

class PropertyViewModelTest : public ::testing::Test {
};

TEST_F(PropertyViewModelTest, initialState)
{
    SessionModel model;
    PropertyViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), model.rootItem());
}

TEST_F(PropertyViewModelTest, baseItem)
{
    SessionModel model;
    model.insertItem<SessionItem>();

    PropertyViewModel viewModel(&model);

    // Root item has default tag and all items considered as top items.
    // PropertyViewModel shouldn't see any items.
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

TEST_F(PropertyViewModelTest, propertyItem)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>();

    parent->registerTag(TagInfo::universalTag("universal_tag"));
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    model.insertItem<SessionItem>(parent, "universal_tag");
    model.insertItem<PropertyItem>(parent, "property_tag");
    model.insertItem<SessionItem>(parent, "universal_tag");

    PropertyViewModel viewModel(&model);
    viewModel.setRootSessionItem(parent);

    // View model should see only property item belonging to parent.
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);
}

//! VectorItem in a model.

TEST_F(PropertyViewModelTest, vectorItem)
{
    SessionModel model;
    auto parent = model.insertItem<VectorItem>();

    PropertyViewModel viewModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 0); // root item doesn't have properties
    EXPECT_EQ(viewModel.columnCount(), 0);

    // switching to vectorItem and checking that it has 3 properties
    viewModel.setRootSessionItem(parent);
    EXPECT_EQ(viewModel.rowCount(), 3);
    EXPECT_EQ(viewModel.columnCount(), 2);
}

//! VectorItem in with hidden component. An item with setVisible(false) set shouldn't appear in a
//! view model. The current implementation is limited and respects this flag only if it was set
//! before the view model creation.

TEST_F(PropertyViewModelTest, vectorItemWithHiddenComponent)
{
    SessionModel model;
    auto vectorItem = model.insertItem<VectorItem>();
    vectorItem->getItem(VectorItem::P_Y)->setVisible(false);

    PropertyViewModel viewModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 0); // root item doesn't have properties
    EXPECT_EQ(viewModel.columnCount(), 0);

    // switching to vectorItem and checking that it has only 2 properties (y-item was skipped).
    viewModel.setRootSessionItem(vectorItem);
    EXPECT_EQ(viewModel.rowCount(), 2);
    EXPECT_EQ(viewModel.columnCount(), 2);

    auto vector_index = QModelIndex();
    auto x_index = viewModel.index(0, 0, vector_index);
    auto z_index = viewModel.index(1, 0, vector_index);
    EXPECT_EQ(viewModel.sessionItemFromIndex(vector_index), vectorItem);
    EXPECT_EQ(viewModel.sessionItemFromIndex(x_index), vectorItem->getItem(VectorItem::P_X));
    EXPECT_EQ(viewModel.sessionItemFromIndex(z_index), vectorItem->getItem(VectorItem::P_Z));

    // attempt to make P_Y visible again
    vectorItem->getItem(VectorItem::P_Y)->setVisible(true);

    // The current implementation is somewhat limited: PropertyViewModel doesn't listen for updates
    // in isVisible flag. If flag is changed after the model creation, item still be invisible.

    vector_index = QModelIndex();
    x_index = viewModel.index(0, 0, vector_index);
    z_index = viewModel.index(1, 0, vector_index);
    EXPECT_EQ(viewModel.sessionItemFromIndex(vector_index), vectorItem);
    EXPECT_EQ(viewModel.sessionItemFromIndex(x_index), vectorItem->getItem(VectorItem::P_X));
    EXPECT_EQ(viewModel.sessionItemFromIndex(z_index), vectorItem->getItem(VectorItem::P_Z));
}

//! LayerItem in a MultiLayer.

TEST_F(PropertyViewModelTest, layerInMultiLayerAsRootItem)
{
    SessionModel model;
    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();
    auto layer = model.insertItem<ToyItems::LayerItem>(multilayer);

    PropertyViewModel viewmodel(&model);
    viewmodel.setRootSessionItem(layer);

    // check layer thickness and color
    EXPECT_EQ(viewmodel.rowCount(), 2);
    EXPECT_EQ(viewmodel.columnCount(), 2);

    // remove multilayer
    model.removeItem(model.rootItem(), {"", 0});

    EXPECT_EQ(viewmodel.rowCount(), 0);
    EXPECT_EQ(viewmodel.columnCount(), 0);
}
