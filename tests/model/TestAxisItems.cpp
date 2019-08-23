#include "google_test.h"
#include "axisitems.h"

using namespace ModelView;

//! Testing AxisItems.

class TestAxisItems : public ::testing::Test
{
public:
    ~TestAxisItems();
};

TestAxisItems::~TestAxisItems() = default;

//! Initial state

TEST_F(TestAxisItems, initialState)
{
    FixedBinAxisItem axis;
    std::vector<double> expected{0.5};
    EXPECT_EQ(axis.binCenters(), expected);
}

//! Factory method

TEST_F(TestAxisItems, fixedBinAxisFactory)
{
    auto axis = FixedBinAxisItem::create(3, 1.0, 4.0);

    EXPECT_EQ(axis->property(FixedBinAxisItem::P_NBINS), 3);
    EXPECT_EQ(axis->property(FixedBinAxisItem::P_MIN), 1.0);
    EXPECT_EQ(axis->property(FixedBinAxisItem::P_MAX), 4.0);

    std::vector<double> expected{1.5, 2.5, 3.5};
    EXPECT_EQ(axis->binCenters(), expected);
}
