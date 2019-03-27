#include "google_test.h"
#include "sessionitemtags.h"
#include "taginfo.h"
#include "test_utils.h"

using namespace ModelView;

//! Tests for SessionItemTags class.

class TestSessionItemTags : public ::testing::Test
{
public:
    ~TestSessionItemTags();
};

TestSessionItemTags::~TestSessionItemTags() = default;

//! Initial state of emty SessionItemTags.

TEST_F(TestSessionItemTags, initialState)
{
    const std::string name("tag");
    SessionItemTags tag;
    EXPECT_EQ(tag.defaultTagName(), "");

    EXPECT_FALSE(tag.exists("abc"));
}

//! Registering tags.

TEST_F(TestSessionItemTags, registerTag)
{
    const std::string name("tag");
    SessionItemTags tag;

    tag.registerTag(TagInfo::universalTag("abc"));
    EXPECT_TRUE(tag.exists("abc"));
    EXPECT_EQ(tag.defaultTagName(), "");

    // registering default tag
    tag.registerTag(TagInfo::universalTag("abc2"), /*set_as_default*/true);
    EXPECT_TRUE(tag.exists("abc2"));
    EXPECT_EQ(tag.defaultTagName(), "abc2");

    // registering tag with same name is not allowed
    EXPECT_THROW(tag.registerTag(TagInfo::universalTag("abc")), std::runtime_error);
}
