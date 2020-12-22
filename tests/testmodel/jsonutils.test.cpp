// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonutils.h"

#include "google_test.h"
#include "mvvm/utils/reallimits.h"
#include <limits>

using namespace ModelView;

class JsonUtilsTest : public ::testing::Test {
};

TEST_F(JsonUtilsTest, toString)
{
    EXPECT_EQ(JsonUtils::ToString(RealLimits::limitless()), "limitless");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::positive()), "positive");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::nonnegative()), "nonnegative");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::lowerLimited(1.0)), "lowerlimited");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::lowerLimited(1.042)), "lowerlimited");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::lowerLimited(-0.99)), "lowerlimited");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::upperLimited(1.0)), "upperlimited");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::limited(-1.0, 2.0)), "limited");
}

TEST_F(JsonUtilsTest, CreateLimits)
{
    EXPECT_EQ(JsonUtils::CreateLimits("limitless"), RealLimits::limitless());
    EXPECT_EQ(JsonUtils::CreateLimits("positive"), RealLimits::positive());
    EXPECT_EQ(JsonUtils::CreateLimits("nonnegative"), RealLimits::nonnegative());
    EXPECT_EQ(JsonUtils::CreateLimits("lowerlimited", 1.0, 0.0), RealLimits::lowerLimited(1.0));
    EXPECT_EQ(JsonUtils::CreateLimits("upperlimited", 0.0, 42.0), RealLimits::upperLimited(42.0));
    EXPECT_EQ(JsonUtils::CreateLimits("limited", -1.0, 2.0), RealLimits::limited(-1.0, 2.0));
}
