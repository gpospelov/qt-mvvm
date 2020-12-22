// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/tagrow.h"

#include "google_test.h"

using namespace ModelView;

//! Testing AxisItems.

class TagRowTest : public ::testing::Test {
public:
    TagRow test_method(const TagRow& input) { return input; }
};

//! Initial state.

TEST_F(TagRowTest, initialState)
{
    TagRow tagrow;
    EXPECT_EQ(tagrow.tag, "");
    EXPECT_EQ(tagrow.row, -1);
}

//! Brace initializer.

TEST_F(TagRowTest, braceInitializer)
{
    TagRow tagrow{"abc", 42};
    EXPECT_EQ(tagrow.tag, "abc");
    EXPECT_EQ(tagrow.row, 42);

    tagrow = {};
    EXPECT_EQ(tagrow.tag, "");
    EXPECT_EQ(tagrow.row, -1);

    tagrow = {"cde", 43};
    EXPECT_EQ(tagrow.tag, "cde");
    EXPECT_EQ(tagrow.row, 43);

    TagRow tagrow2 = {"cde"};
    EXPECT_EQ(tagrow2.tag, "cde");
    EXPECT_EQ(tagrow2.row, -1);
}

//! Equality operators.

TEST_F(TagRowTest, equalityOperators)
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

TEST_F(TagRowTest, assignmentOperator)
{
    TagRow tag1;
    TagRow tag2{"abc", 42};

    tag1 = tag2;
    EXPECT_EQ(tag1.row, 42);
    EXPECT_EQ(tag1.tag, "abc");
}

//! Factory methods.

TEST_F(TagRowTest, factoryMethods)
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

//! Implicit type convertion

TEST_F(TagRowTest, implicitConvertion)
{
    auto tagrow = test_method("abc");
    EXPECT_EQ(tagrow.tag, "abc");
    EXPECT_EQ(tagrow.row, -1);
}

//! Find next tagrow.

TEST_F(TagRowTest, next)
{
    TagRow tagrow{"tag", 0};
    EXPECT_EQ(tagrow.next().tag, "tag");
    EXPECT_EQ(tagrow.next().row, 1);
}

//! Find previous tagrow.

TEST_F(TagRowTest, prev)
{
    TagRow tagrow{"tag", 1};
    EXPECT_EQ(tagrow.prev().tag, "tag");
    EXPECT_EQ(tagrow.prev().row, 0);
}
