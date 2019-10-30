#include "google_test.h"
#include "stringutils.h"

using namespace ModelView;

class TestStringUtils : public ::testing::Test
{
public:
    ~TestStringUtils();

};

TestStringUtils::~TestStringUtils() = default;

TEST_F(TestStringUtils, ScientificDoubleToString)
{
    const int precision = 6;

    EXPECT_EQ(Utils::ScientificDoubleToString(0.0, precision), "0.0e+00");
    EXPECT_EQ(Utils::ScientificDoubleToString(1.0, precision), "1.0e+00");
    EXPECT_EQ(Utils::ScientificDoubleToString(3.0/4.0, precision), "7.5e-01");
    EXPECT_EQ(Utils::ScientificDoubleToString(4.0/3.0, precision), "1.333333e+00");
    EXPECT_EQ(Utils::ScientificDoubleToString(1000000., precision), "1.0e+06");
}

TEST_F(TestStringUtils, DoubleToString)
{
    const int precision = 4;

    EXPECT_EQ(Utils::DoubleToString(0.0, precision), "0.0");
    EXPECT_EQ(Utils::DoubleToString(1.001, precision), "1.001");
    EXPECT_EQ(Utils::DoubleToString(1.0001, precision), "1.0");
}
