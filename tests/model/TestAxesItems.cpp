#include "google_test.h"
#include "axesitems.h"

using namespace ModelView;

//! Testing AxesItems.

class TestAxesItems : public ::testing::Test
{
public:
    ~TestAxesItems();
};

TestAxesItems::~TestAxesItems() = default;

//! Initial state

TEST_F(TestAxesItems, initialState)
{
    FixedBinAxisItem axis;
    std::vector<double> expected{0.5};
    EXPECT_EQ(axis.binCenters(), expected);
}

//! Factory method

TEST_F(TestAxesItems, fixedBinAxisFactory)
{
    auto axis = FixedBinAxisItem::create(3, 1.0, 4.0);

    EXPECT_EQ(axis->getItem(FixedBinAxisItem::P_NBINS)->data(), 3);
    EXPECT_EQ(axis->getItem(FixedBinAxisItem::P_MIN)->data(), 1.0);
    EXPECT_EQ(axis->getItem(FixedBinAxisItem::P_MAX)->data(), 4.0);

    std::vector<double> expected{1.5, 2.5, 3.5};
    EXPECT_EQ(axis->binCenters(), expected);
}
