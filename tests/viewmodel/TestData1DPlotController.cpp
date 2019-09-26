#include "google_test.h"

using namespace ModelView;

//! Testing Data1DPlotController.

class Data1DPlotController : public ::testing::Test
{
public:
    ~Data1DPlotController();
};

Data1DPlotController::~Data1DPlotController() = default;

//! Initial state.

TEST_F(Data1DPlotController, initialState)
{
    EXPECT_EQ(1, 1);
}
