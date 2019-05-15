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

TEST_F(RealLimitsTest, LimitsInitial)
{
    RealLimits limits;

    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
}

TEST_F(RealLimitsTest, LimitsSetLimit)
{
    RealLimits limits;

    // set limit [-1.0, 10.0[
    limits.setLimits(-1.0, 10.0);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_TRUE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(-1.0, limits.lowerLimit());
    EXPECT_EQ(10.0, limits.upperLimit());

    EXPECT_FALSE(limits.isInRange(-2.0));
    EXPECT_TRUE(limits.isInRange(-1.0));
    EXPECT_TRUE(limits.isInRange(0.0));
    EXPECT_TRUE(limits.isInRange(9.0));
    EXPECT_FALSE(limits.isInRange(10.0));
    EXPECT_FALSE(limits.isInRange(20.0));

    // [inf, -10.0[
    limits.removeLowerLimit();
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_EQ(0.0, limits.lowerLimit());

    EXPECT_TRUE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(limits.isInRange(-2.0));
    EXPECT_TRUE(limits.isInRange(9.0));
    EXPECT_FALSE(limits.isInRange(10.0));
    EXPECT_FALSE(limits.isInRange(std::numeric_limits<double>::infinity()));

    // [2.1, -10.0[
    limits.setLowerLimit(2.1);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_EQ(2.1, limits.lowerLimit());

    EXPECT_FALSE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(limits.isInRange(2.0));
    EXPECT_TRUE(limits.isInRange(2.1));

    //[2.1, inf]
    limits.removeUpperLimit();
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_EQ(0.0, limits.upperLimit());

    EXPECT_FALSE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(limits.isInRange(2.0));
    EXPECT_TRUE(limits.isInRange(2.1));
    EXPECT_TRUE(limits.isInRange(20.0));
    EXPECT_TRUE(limits.isInRange(std::numeric_limits<double>::infinity()));

    // [2.1, 2.2[
    limits.setUpperLimit(2.2);
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_EQ(2.2, limits.upperLimit());
    EXPECT_TRUE(limits.hasLowerAndUpperLimits());
    EXPECT_TRUE(limits.isInRange(2.15));
    EXPECT_FALSE(limits.isInRange(2.2));

    // remove limit
    limits.removeLimits();
    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());

    EXPECT_TRUE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(limits.isInRange(std::numeric_limits<double>::infinity()));
}

TEST_F(RealLimitsTest, LimitsLowerLimited)
{
    RealLimits limits = RealLimits::lowerLimited(5.0);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(5.0, limits.lowerLimit());
    EXPECT_EQ(0.0, limits.upperLimit());
}

TEST_F(RealLimitsTest, LimitsUpperLimited)
{
    RealLimits limits = RealLimits::upperLimited(5.0);
    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(0.0, limits.lowerLimit());
    EXPECT_EQ(5.0, limits.upperLimit());
}

TEST_F(RealLimitsTest, LimitsLimited)
{
    RealLimits limits = RealLimits::limited(-10.0, 2.0);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_TRUE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(-10.0, limits.lowerLimit());
    EXPECT_EQ(2.0, limits.upperLimit());
}

TEST_F(RealLimitsTest, LimitsLimitless)
{
    RealLimits limits = RealLimits::limitless();

    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
}

TEST_F(RealLimitsTest, ComparisonOperators)
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

TEST_F(RealLimitsTest, CopyConstructor)
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
