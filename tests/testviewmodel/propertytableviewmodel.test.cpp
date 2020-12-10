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
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/propertytableviewmodel.h>

using namespace ModelView;

class PropertyTableViewModelTest : public ::testing::Test
{
public:
    ~PropertyTableViewModelTest();
};

PropertyTableViewModelTest::~PropertyTableViewModelTest() = default;

TEST_F(PropertyTableViewModelTest, initialState)
{
    SessionModel model;
    PropertyTableViewModel viewModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), model.rootItem());
}

TEST_F(PropertyTableViewModelTest, baseItem)
{
    SessionModel model;
    model.insertItem<SessionItem>();

    PropertyTableViewModel viewModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

TEST_F(PropertyTableViewModelTest, propertyItem)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>();

    parent->registerTag(TagInfo::universalTag("universal_tag"));
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    model.insertItem<SessionItem>(parent, "universal_tag");
    model.insertItem<PropertyItem>(parent, "property_tag");
    model.insertItem<SessionItem>(parent, "universal_tag");

    PropertyTableViewModel viewModel(&model);

    // one cell corresponding to single item at property_tag of our parent
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 1);

    viewModel.setRootSessionItem(parent);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! VectorItem in a model.

TEST_F(PropertyTableViewModelTest, vectorItem)
{
    SessionModel model;
    auto parent = model.insertItem<VectorItem>();

    PropertyTableViewModel viewModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 3);

    // switching to vectorItem and checking that it has 3 properties
    viewModel.setRootSessionItem(parent);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! MultiLayer with layers, view model still looks to the RootItem.
//! No MultiLayer should be visible in table.

TEST_F(PropertyTableViewModelTest, multiLayerAndRootItem)
{
    SessionModel model;
    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::LayerItem>(multilayer);
    model.insertItem<ToyItems::LayerItem>(multilayer);

    PropertyTableViewModel viewModel(&model);

    // ViewModel should be empty, since we are looking to RootItem.
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! MultiLayer with layers, multilayer is given as root index.

TEST_F(PropertyTableViewModelTest, multiLayer)
{
    SessionModel model;
    auto multilayer = model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::LayerItem>(multilayer);
    model.insertItem<ToyItems::LayerItem>(multilayer);

    PropertyTableViewModel viewModel(&model);
    viewModel.setRootSessionItem(multilayer);

    EXPECT_EQ(viewModel.rowCount(), 2);    // two layers
    EXPECT_EQ(viewModel.columnCount(), 2); // layer thickness and color

    // add another layer
    model.insertItem<ToyItems::LayerItem>(multilayer);
    EXPECT_EQ(viewModel.rowCount(), 3);    // two layers
    EXPECT_EQ(viewModel.columnCount(), 2); // layer thickness and color

    // switching view model back to model's root, table should be empty
    viewModel.setRootSessionItem(model.rootItem());
    EXPECT_EQ(viewModel.rowCount(), 0);    // two layers
    EXPECT_EQ(viewModel.columnCount(), 0); // layer thickness and color
}
