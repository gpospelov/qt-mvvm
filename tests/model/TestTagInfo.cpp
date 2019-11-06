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

class TestTagInfo : public ::testing::Test
{
public:
    ~TestTagInfo();
};

TestTagInfo::~TestTagInfo() = default;

TEST_F(TestTagInfo, initialState)
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

TEST_F(TestTagInfo, defaultTag)
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

TEST_F(TestTagInfo, propertyTag)
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
