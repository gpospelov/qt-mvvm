// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/model/taginfo.h>

using namespace ModelView;

//! Tests of TagInfo class.

class TagInfoTest : public ::testing::Test
{
public:
    ~TagInfoTest();
};

TagInfoTest::~TagInfoTest() = default;

TEST_F(TagInfoTest, initialState)
{
    TagInfo tag;
    EXPECT_EQ(tag.name(), std::string());
    EXPECT_EQ(tag.min(), 0);
    EXPECT_EQ(tag.max(), -1);
    EXPECT_FALSE(tag.isSinglePropertyTag());
    EXPECT_TRUE(tag.isValidChild(""));
    EXPECT_TRUE(tag.isValidChild("abc"));
}

//! Testing default tag intended for storing unlimited amount of items of any type.

TEST_F(TagInfoTest, defaultTag)
{
    // initial state
    TagInfo tag = TagInfo::universalTag("name");
    EXPECT_EQ(tag.name(), std::string("name"));
    EXPECT_EQ(tag.min(), 0);
    EXPECT_EQ(tag.max(), -1);
    EXPECT_FALSE(tag.isSinglePropertyTag());
    EXPECT_TRUE(tag.isValidChild(""));
    EXPECT_TRUE(tag.isValidChild("abc"));
}

//! Testing property tag intended for storing single PropertyItem.

TEST_F(TagInfoTest, propertyTag)
{
    // initial state
    TagInfo tag = TagInfo::propertyTag("name", "model_type");

    EXPECT_EQ(tag.name(), std::string("name"));
    EXPECT_EQ(tag.min(), 1);
    EXPECT_EQ(tag.max(), 1);
    EXPECT_TRUE(tag.isSinglePropertyTag());
    EXPECT_TRUE(tag.isValidChild("model_type"));
    EXPECT_FALSE(tag.isValidChild("abc"));
}

//! Testing equality operators.

TEST_F(TagInfoTest, equalityOperator)
{
    // default constructor
    TagInfo tag1, tag2;
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_FALSE(tag1 != tag2);

    // same property tag
    TagInfo tag3 = TagInfo::propertyTag("name", "model_type");
    TagInfo tag4 = TagInfo::propertyTag("name", "model_type");
    EXPECT_TRUE(tag3 == tag4);
    EXPECT_FALSE(tag3 != tag4);

    // same universal tag
    TagInfo tag5 = TagInfo::universalTag("name");
    TagInfo tag6 = TagInfo::universalTag("name");
    EXPECT_TRUE(tag5 == tag6);
    EXPECT_FALSE(tag5 != tag6);

    // different tag
    TagInfo tag7("tag7", 0, 1, std::vector<std::string>());
    TagInfo tag8("tag8", 0, 1, std::vector<std::string>());
    EXPECT_FALSE(tag7 == tag8);
    EXPECT_TRUE(tag7 != tag8);
}
