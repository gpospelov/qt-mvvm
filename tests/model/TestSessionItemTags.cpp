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

    EXPECT_FALSE(tag.exists("abc"));
}

//! Registering tags.

TEST_F(TestSessionItemTags, registerTag)
{
    const std::string name("tag");
    SessionItemTags tag;

    tag.registerTag(TagInfo::universalTag("abc"));
    EXPECT_TRUE(tag.exists("abc"));
}
