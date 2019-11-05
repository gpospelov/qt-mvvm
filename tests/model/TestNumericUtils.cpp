#include "google_test.h"
#include <mvvm/utils/numericutils.h>
#include <cmath>

using namespace ModelView;

class TestNumericUtils : public ::testing::Test
{
public:
    ~TestNumericUtils();

};

TestNumericUtils::~TestNumericUtils() = default;

TEST_F(TestNumericUtils, areAlmostEqual)
{
    EXPECT_TRUE(Utils::AreAlmostEqual(0.0, 0.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(1.0, 1.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(10.0/100.0, 100.0/1000.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(std::sin(0.0), 0.0));
    EXPECT_FALSE(Utils::AreAlmostEqual(std::cos(0.0), 0.0));
}
