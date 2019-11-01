#include "axisitems.h"
#include "google_test.h"

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
    EXPECT_EQ(axis.size(), 1);
}

//! Initial state

TEST_F(TestAxisItems, viewportAxisInitialState)
{
    ViewportAxisItem axis;
    EXPECT_EQ(axis.property(ViewportAxisItem::P_MIN), 0.0);
    EXPECT_EQ(axis.property(ViewportAxisItem::P_MAX), 1.0);
    EXPECT_FALSE(axis.property(ViewportAxisItem::P_IS_LOG).value<bool>());
}

//! ViewportAxisItem::setRange

TEST_F(TestAxisItems, viewportAxisSetRange)
{
    ViewportAxisItem axis;

    // default range
    auto [lower, upper] = axis.range();
    EXPECT_EQ(lower, 0.0);
    EXPECT_EQ(upper, 1.0);

    axis.set_range(1.0, 2.0);
    EXPECT_EQ(axis.property(ViewportAxisItem::P_MIN), 1.0);
    EXPECT_EQ(axis.property(ViewportAxisItem::P_MAX), 2.0);
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
    EXPECT_EQ(axis->size(), 3);
}

//! Range method.

TEST_F(TestAxisItems, fixedBinAxisRange)
{
    auto axis = FixedBinAxisItem::create(3, 1.0, 4.0);

    auto [lower, upper] = axis->range();
    EXPECT_EQ(lower, 1.0);
    EXPECT_EQ(upper, 4.0);
}
