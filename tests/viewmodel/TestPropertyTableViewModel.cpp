#include "google_test.h"
#include "propertytableviewmodel.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "taginfo.h"

using namespace ModelView;

class TestPropertyTableViewModel : public ::testing::Test
{
public:
    ~TestPropertyTableViewModel();
};

TestPropertyTableViewModel::~TestPropertyTableViewModel() = default;

TEST_F(TestPropertyTableViewModel, initialState)
{
    PropertyTableViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(QModelIndex()), nullptr);
}

TEST_F(TestPropertyTableViewModel, baseItem)
{
    SessionModel model;
    model.insertNewItem(Constants::BaseType);

    PropertyTableViewModel viewModel;
    viewModel.setSessionModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 0); // FIXME don't understand why is not 1 for ViewEmptyItem
}

//! VectorItem in a model.

TEST_F(TestPropertyTableViewModel, vectorItem)
{
    SessionModel model;
    auto parent = model.insertNewItem(Constants::VectorType);

    PropertyTableViewModel viewModel;
    viewModel.setSessionModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 3);

    // switching to vectorItem and checking that it has 3 properties
    viewModel.setRootSessionItem(parent);
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}
