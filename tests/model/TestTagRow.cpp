// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#include "google_test.h"
#include <mvvm/model/tagrow.h>

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

    tagrow = {"cde", 43};
    EXPECT_EQ(tagrow.tag, "cde");
    EXPECT_EQ(tagrow.row, 43);
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
    EXPECT_FALSE(tag7 == tag8);
    EXPECT_TRUE(tag7 != tag8);
}

//! Assignment operators.

TEST_F(TestTagRow, assignmentOperator)
{
    TagRow tag1;
    TagRow tag2 {"abc", 42};

    tag1 = tag2;
    EXPECT_EQ(tag1.row, 42);
    EXPECT_EQ(tag1.tag, "abc");
}

//! Factory methods.

TEST_F(TestTagRow, factoryMethods)
{
    auto tagrow = TagRow::append();
    EXPECT_EQ(tagrow.tag, "");
    EXPECT_EQ(tagrow.row, -1);

    const std::string expected_name("tag");
    tagrow = TagRow::append(expected_name);
    EXPECT_EQ(tagrow.tag, expected_name);
    EXPECT_EQ(tagrow.row, -1);

    tagrow = TagRow::prepend(expected_name);
    EXPECT_EQ(tagrow.tag, expected_name);
    EXPECT_EQ(tagrow.row, 0);
}

