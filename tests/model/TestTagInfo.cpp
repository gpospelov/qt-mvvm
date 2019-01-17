#include "google_test.h"
#include "taginfo.h"

using namespace ModelView;

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
    EXPECT_EQ(tag.childCount(), 0);
    EXPECT_EQ(tag.min(), 0);
    EXPECT_EQ(tag.max(), -1);
    EXPECT_FALSE(tag.maximumReached());
    EXPECT_FALSE(tag.isSingleItemTag());
    EXPECT_TRUE(tag.isValidChild(""));
    EXPECT_TRUE(tag.isValidChild("abc"));
}

//! Testing default tag intended for storing unlimited amount of items of any type.

TEST_F(TestTagInfo, defaultTag)
{
    // initial state
    TagInfo tag = TagInfo::defaultTag("name");
    EXPECT_EQ(tag.name(), std::string("name"));
    EXPECT_EQ(tag.childCount(), 0);
    EXPECT_EQ(tag.min(), 0);
    EXPECT_EQ(tag.max(), -1);
    EXPECT_FALSE(tag.maximumReached());
    EXPECT_FALSE(tag.isSingleItemTag());
    EXPECT_TRUE(tag.isValidChild(""));
    EXPECT_TRUE(tag.isValidChild("abc"));

    // adding child
    tag.add();
    EXPECT_EQ(tag.childCount(), 1u);
    tag.add();
    EXPECT_EQ(tag.childCount(), 2u);

    // removing children
    tag.remove();
    EXPECT_EQ(tag.childCount(), 1u);
    tag.remove();
    EXPECT_EQ(tag.childCount(), 0u);
    EXPECT_THROW(tag.remove(), std::runtime_error);
}

//! Testing property tag intended for storing single PropertyItem.

TEST_F(TestTagInfo, propertyTag)
{
    // initial state
    TagInfo tag = TagInfo::propertyTag("name", "model_type");

    EXPECT_EQ(tag.name(), std::string("name"));
    EXPECT_EQ(tag.childCount(), 0);
    EXPECT_EQ(tag.min(), 1);
    EXPECT_EQ(tag.max(), 1);
    EXPECT_FALSE(tag.maximumReached());
    EXPECT_FALSE(tag.isSingleItemTag());
    EXPECT_TRUE(tag.isValidChild("model_type"));
    EXPECT_FALSE(tag.isValidChild("abc"));

    // adding valid child once is allowed
    tag.add();
    EXPECT_EQ(tag.childCount(), 1u);

    // it shouldn't be possible to add/remove children after
    EXPECT_THROW(tag.remove(), std::runtime_error);
    EXPECT_THROW(tag.add(), std::runtime_error);
}

