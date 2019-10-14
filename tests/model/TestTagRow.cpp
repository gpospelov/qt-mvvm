#include "google_test.h"
#include "tagrow.h"

using namespace ModelView;

//! Testing AxisItems.

class TestTagRow : public ::testing::Test
{
public:
    ~TestTagRow();
};

TestTagRow::~TestTagRow() = default;

//! Initial state.

TEST_F(TestTagRow, initialState)
{
    TagRow tagrow;
    EXPECT_EQ(tagrow.tag, "");
    EXPECT_EQ(tagrow.row, -1);
}

//! Brace initializer.

TEST_F(TestTagRow, braceInitializer)
{
    TagRow tagrow {"abc", 42};
    EXPECT_EQ(tagrow.tag, "abc");
    EXPECT_EQ(tagrow.row, 42);

    tagrow = {};
    EXPECT_EQ(tagrow.tag, "");
    EXPECT_EQ(tagrow.row, -1);
}

//! Equality operators.
TEST_F(TestTagRow, equalityOperators)
{
    TagRow tag1;
    TagRow tag2;
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_FALSE(tag1 != tag2);

    TagRow tag3 = {"abc", 42};
    TagRow tag4 = {"abc", 42};
    EXPECT_TRUE(tag3 == tag4);
    EXPECT_FALSE(tag3 != tag4);

    TagRow tag5 = {"abc", 42};
    TagRow tag6 = {"abc", 43};
    EXPECT_FALSE(tag5 == tag6);
    EXPECT_TRUE(tag5 != tag6);

    TagRow tag7 = {"a", 42};
    TagRow tag8 = {"b", 42};
    EXPECT_FALSE(tag5 == tag6);
    EXPECT_TRUE(tag5 != tag6);
}
