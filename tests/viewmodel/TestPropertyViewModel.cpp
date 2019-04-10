#include "propertyviewmodel.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
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
    auto top1 = model.insertNewItem(Constants::BaseType);

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
    auto parent = model.insertNewItem(Constants::BaseType);

    parent->registerTag(TagInfo::universalTag("universal_tag"));
    parent->registerTag(TagInfo::propertyTag("property_tag", Constants::PropertyType));

    model.insertNewItem(Constants::BaseType, parent, "universal_tag");
    model.insertNewItem(Constants::PropertyType, parent, "property_tag");
    model.insertNewItem(Constants::BaseType, parent, "universal_tag");

    PropertyViewModel viewModel;
    viewModel.setSessionModel(&model);
    viewModel.setRootSessionItem(parent);

    // View model should see only property item belonging to parent.
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);
}
