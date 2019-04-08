#include "propertyviewmodel.h"
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
