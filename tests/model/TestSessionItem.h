#include <gtest/gtest.h>

class TestSessionItem : public ::testing::Test
{
public:
    ~TestSessionItem();
};

TestSessionItem::~TestSessionItem() = default;

TEST_F(TestSessionItem, test_linkInstrumentManager)
{
    EXPECT_EQ(1, 2);
}
