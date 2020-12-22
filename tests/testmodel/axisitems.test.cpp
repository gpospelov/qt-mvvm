// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/axisitems.h"

#include "google_test.h"

using namespace ModelView;

//! Testing AxisItems.

class AxisItemsTest : public ::testing::Test {
};

//! Initial state

TEST_F(AxisItemsTest, viewportAxisInitialState)
{
    ViewportAxisItem axis;
    EXPECT_EQ(axis.property<double>(ViewportAxisItem::P_MIN), 0.0);
    EXPECT_EQ(axis.property<double>(ViewportAxisItem::P_MAX), 1.0);
    EXPECT_FALSE(axis.property<bool>(ViewportAxisItem::P_IS_LOG));
}

//! ViewportAxisItem::setRange

TEST_F(AxisItemsTest, viewportAxisSetRange)
{
    ViewportAxisItem axis;

    // default range
    auto [lower, upper] = axis.range();
    EXPECT_EQ(lower, 0.0);
    EXPECT_EQ(upper, 1.0);

    axis.set_range(1.0, 2.0);
    EXPECT_EQ(axis.property<double>(ViewportAxisItem::P_MIN), 1.0);
    EXPECT_EQ(axis.property<double>(ViewportAxisItem::P_MAX), 2.0);
}

//! Factory method for FixedBinAxisItem.

TEST_F(AxisItemsTest, fixedBinAxisInitialState)
{
    FixedBinAxisItem axis;
    EXPECT_EQ(axis.property<double>(FixedBinAxisItem::P_MIN), 0.0);
    EXPECT_EQ(axis.property<double>(FixedBinAxisItem::P_MAX), 1.0);
    EXPECT_EQ(axis.property<int>(FixedBinAxisItem::P_NBINS), 1);
    EXPECT_EQ(axis.binCenters(), std::vector<double>{0.5});
    EXPECT_EQ(axis.size(), 1);
    auto [lower, upper] = axis.range();
    EXPECT_EQ(lower, 0.0);
    EXPECT_EQ(upper, 1.0);
}

//! Factory method for FixedBinAxisItem.

TEST_F(AxisItemsTest, fixedBinAxisSetParameters)
{
    FixedBinAxisItem axis;
    axis.setParameters(3, 1.0, 4.0);

    EXPECT_EQ(axis.property<int>(FixedBinAxisItem::P_NBINS), 3);
    EXPECT_EQ(axis.property<double>(FixedBinAxisItem::P_MIN), 1.0);
    EXPECT_EQ(axis.property<double>(FixedBinAxisItem::P_MAX), 4.0);

    std::vector<double> expected{1.5, 2.5, 3.5};
    EXPECT_EQ(axis.binCenters(), expected);
    EXPECT_EQ(axis.size(), 3);
}

//! Factory method for FixedBinAxisItem.

TEST_F(AxisItemsTest, fixedBinAxisFactory)
{
    auto axis = FixedBinAxisItem::create(3, 1.0, 4.0);

    EXPECT_EQ(axis->property<int>(FixedBinAxisItem::P_NBINS), 3);
    EXPECT_EQ(axis->property<double>(FixedBinAxisItem::P_MIN), 1.0);
    EXPECT_EQ(axis->property<double>(FixedBinAxisItem::P_MAX), 4.0);

    std::vector<double> expected{1.5, 2.5, 3.5};
    EXPECT_EQ(axis->binCenters(), expected);
    EXPECT_EQ(axis->size(), 3);
}

//! Range method.

TEST_F(AxisItemsTest, fixedBinAxisRange)
{
    auto axis = FixedBinAxisItem::create(3, 1.0, 4.0);

    auto [lower, upper] = axis->range();
    EXPECT_EQ(lower, 1.0);
    EXPECT_EQ(upper, 4.0);
}

TEST_F(AxisItemsTest, PointwiseAxisInitialState)
{
    PointwiseAxisItem axis;
    std::vector<double> expected_centers = {0.0, 1.0};
    EXPECT_EQ(axis.binCenters(), expected_centers);
    EXPECT_EQ(axis.size(), 2);
}

TEST_F(AxisItemsTest, PointwiseAxisSetParameters)
{
    std::vector<double> expected_centers{1.0, 2.0, 3.0};
    PointwiseAxisItem axis;
    axis.setParameters(expected_centers);
    EXPECT_EQ(axis.binCenters(), expected_centers);
    EXPECT_EQ(axis.size(), 3);
}

TEST_F(AxisItemsTest, PointwiseAxisCreate)
{
    std::vector<double> expected_centers{1.0, 2.0, 3.0};
    auto axis = PointwiseAxisItem::create(expected_centers);
    EXPECT_EQ(axis->binCenters(), expected_centers);
    EXPECT_EQ(axis->size(), 3);
}
