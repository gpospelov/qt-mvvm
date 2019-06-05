#include "google_test.h"
#include "propertytableviewmodel.h"

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
