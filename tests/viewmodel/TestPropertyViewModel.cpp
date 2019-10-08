#include "propertyviewmodel.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "propertyitem.h"
#include "vectoritem.h"
#include "google_test.h"

using namespace ModelView;

//! Tests for PropertyViewModel class.

class TestPropertyViewModel : public ::testing::Test
{
public:
    ~TestPropertyViewModel();
};

TestPropertyViewModel::~TestPropertyViewModel() = default;

TEST_F(TestPropertyViewModel, initialState)
{
    PropertyViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), nullptr);
}

TEST_F(TestPropertyViewModel, baseItem)
{
    SessionModel model;
    model.insertItem<SessionItem>();

    PropertyViewModel viewModel;
    viewModel.setSessionModel(&model);

    // Root item has default tag and all items considered as top items.
    // PropertyViewModel shouldn't see any items.
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 2);
}

TEST_F(TestPropertyViewModel, propertyItem)
{
    SessionModel model;
    auto parent = model.insertItem<SessionItem>();

    parent->registerTag(TagInfo::universalTag("universal_tag"));
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    model.insertItem<SessionItem>(parent, "universal_tag");
    model.insertItem<PropertyItem>(parent, "property_tag");
    model.insertItem<SessionItem>(parent, "universal_tag");

    PropertyViewModel viewModel;
    viewModel.setSessionModel(&model);
    viewModel.setRootSessionItem(parent);

    // View model should see only property item belonging to parent.
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);
}

//! VectorItem in a model.

TEST_F(TestPropertyViewModel, vectorItem)
{
    SessionModel model;
    auto parent = model.insertItem<VectorItem>();

    PropertyViewModel viewModel;
    viewModel.setSessionModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 0); // root item doesn't have properties
    EXPECT_EQ(viewModel.columnCount(), 2);

    // switching to vectorItem and checking that it has 3 properties
    viewModel.setRootSessionItem(parent);
    EXPECT_EQ(viewModel.rowCount(), 3);
    EXPECT_EQ(viewModel.columnCount(), 2);
}
