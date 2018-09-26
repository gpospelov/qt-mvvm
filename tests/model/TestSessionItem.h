#include <gtest/gtest.h>

class TestSessionItem : public ::testing::Test
{
public:
    ~TestSessionItem();
};

TestSessionItem::~TestSessionItem() = default;

TEST_F(TestSessionItem, initialState)
{
    EXPECT_EQ(1, 1);
}

TEST_F(TestSessionItem, expectedValue)
{
    EXPECT_EQ(1, 1);
}
