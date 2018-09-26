#include <gtest/gtest.h>

class TestAnother : public ::testing::Test
{
public:
    ~TestAnother();
};

TestAnother::~TestAnother() = default;

TEST_F(TestAnother, initialState)
{
    EXPECT_EQ(1, 1);
}

TEST_F(TestAnother, expectedValue)
{
    EXPECT_EQ(1, 1);
}

TEST_F(TestAnother, andAnother)
{
    EXPECT_EQ(1, 1);
}
