// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
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
    PropertyTableViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), nullptr);
}

TEST_F(PropertyTableViewModelTest, baseItem)
{
    SessionModel model;
    model.insertItem<SessionItem>();

    PropertyTableViewModel viewModel;
    viewModel.setSessionModel(&model);

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

    PropertyTableViewModel viewModel;
    viewModel.setSessionModel(&model);

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

    PropertyTableViewModel viewModel;
    viewModel.setSessionModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 3);

    // switching to vectorItem and checking that it has 3 properties
    viewModel.setRootSessionItem(parent);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}
