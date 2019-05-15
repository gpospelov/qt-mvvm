#include "google_test.h"
#include "reallimits.h"
#include <limits>

using namespace ModelView;

class RealLimitsTest : public ::testing::Test
{
protected:
    ~RealLimitsTest();
};

RealLimitsTest::~RealLimitsTest() = default;

TEST_F(RealLimitsTest, initialState)
{
    RealLimits limits;

    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
    EXPECT_TRUE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(limits.isInRange(0.0));
    EXPECT_TRUE(limits.isInRange(std::numeric_limits<double>::infinity()));

    EXPECT_FALSE(limits.isPositive());
    EXPECT_FALSE(limits.isNonnegative());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLimited());
}

TEST_F(RealLimitsTest, lowerLimited)
{
    RealLimits limits = RealLimits::lowerLimited(5.0);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(5.0, limits.lowerLimit());
    EXPECT_EQ(0.0, limits.upperLimit());

    EXPECT_FALSE(limits.isPositive());
    EXPECT_FALSE(limits.isNonnegative());
    EXPECT_TRUE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLimited());
}

TEST_F(RealLimitsTest, upperLimited)
{
    // [-inf, 5.0[
    RealLimits limits = RealLimits::upperLimited(5.0);
    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(0.0, limits.lowerLimit()); // FIXME
    EXPECT_EQ(5.0, limits.upperLimit());

    EXPECT_TRUE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(limits.isInRange(-2.0));
    EXPECT_FALSE(limits.isInRange(5.0));
    EXPECT_FALSE(limits.isInRange(std::numeric_limits<double>::infinity()));

    EXPECT_FALSE(limits.isPositive());
    EXPECT_FALSE(limits.isNonnegative());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_TRUE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLimited());
}

TEST_F(RealLimitsTest, limited)
{
    // [-10.0, 2.0[
    RealLimits limits = RealLimits::limited(-10.0, 2.0);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_TRUE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(-10.0, limits.lowerLimit());
    EXPECT_EQ(2.0, limits.upperLimit());

    EXPECT_FALSE(limits.isInRange(-11.0));
    EXPECT_TRUE(limits.isInRange(-9.0));
    EXPECT_TRUE(limits.isInRange(0.0));
    EXPECT_TRUE(limits.isInRange(1.0));
    EXPECT_FALSE(limits.isInRange(2.0));
    EXPECT_FALSE(limits.isInRange(3.0));

    EXPECT_FALSE(limits.isPositive());
    EXPECT_FALSE(limits.isNonnegative());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_TRUE(limits.isLimited());
}

TEST_F(RealLimitsTest, limitless)
{
    RealLimits limits = RealLimits::limitless();

    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
    EXPECT_TRUE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(limits.isInRange(0.0));
    EXPECT_TRUE(limits.isInRange(std::numeric_limits<double>::infinity()));

    EXPECT_FALSE(limits.isPositive());
    EXPECT_FALSE(limits.isNonnegative());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLimited());
}

TEST_F(RealLimitsTest, comparisonOperators)
{
    RealLimits lim1 = RealLimits::limited(1.0, 2.0);
    RealLimits lim2 = RealLimits::limited(1.0, 2.0);
    EXPECT_TRUE(lim1 == lim2);
    EXPECT_FALSE(lim1 != lim2);

    RealLimits lim3 = RealLimits::limitless();
    RealLimits lim4 = RealLimits::limitless();
    EXPECT_TRUE(lim3 == lim4);
    EXPECT_FALSE(lim3 != lim4);

    RealLimits lim5 = RealLimits::lowerLimited(1.0);
    RealLimits lim6 = RealLimits::lowerLimited(1.0);
    EXPECT_TRUE(lim5 == lim6);
    EXPECT_FALSE(lim5 != lim6);

    RealLimits lim7 = RealLimits::upperLimited(1.0);
    RealLimits lim8 = RealLimits::upperLimited(1.0);
    EXPECT_TRUE(lim7 == lim8);
    EXPECT_FALSE(lim7 != lim8);
}

TEST_F(RealLimitsTest, copyConstructor)
{
    RealLimits lim1 = RealLimits::limited(1.0, 2.0);
    RealLimits lim2 = lim1;
    EXPECT_TRUE(lim1 == lim2);
    EXPECT_FALSE(lim1 != lim2);

    RealLimits lim3(lim1);
    EXPECT_TRUE(lim1 == lim3);
    EXPECT_FALSE(lim1 != lim3);
}

TEST_F(RealLimitsTest, toVariant)
{
    RealLimits limit = RealLimits::limited(1.0, 2.0);
    QVariant variant = QVariant::fromValue(limit);

    EXPECT_EQ(variant.value<RealLimits>().isLimited(), limit.isLimited());
    EXPECT_EQ(variant.value<RealLimits>().lowerLimit(), limit.lowerLimit());
    EXPECT_EQ(variant.value<RealLimits>().upperLimit(), limit.upperLimit());
}

TEST_F(RealLimitsTest, variantEquality)
{
    if (ModelView::Comparators::registered()) {
        QVariant var1a = QVariant::fromValue(RealLimits::limited(1.0, 2.0));
        QVariant var1b = QVariant::fromValue(RealLimits::limited(1.0, 2.0));
        QVariant var2 = QVariant::fromValue(RealLimits::lowerLimited(1.0));

        EXPECT_TRUE(var1a == var1b);
        EXPECT_FALSE(var1a == var2);
        EXPECT_FALSE(var1a != var1b);
        EXPECT_TRUE(var1a != var2);
    }
}
