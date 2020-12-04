// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/propertyviewmodel.h>

using namespace ModelView;

//! Tests for PropertyViewModel class.

class PropertyViewModelTest : public ::testing::Test
{
public:
    ~PropertyViewModelTest();
};

PropertyViewModelTest::~PropertyViewModelTest() = default;

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
