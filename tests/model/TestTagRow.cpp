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
}

