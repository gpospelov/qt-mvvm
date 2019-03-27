#include "google_test.h"
#include "sessionitemtags.h"
#include "taginfo.h"
#include "sessionitem.h"
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
    EXPECT_EQ(tag.defaultTag(), "");

    EXPECT_FALSE(tag.exists("abc"));
}

//! Registering tags.

TEST_F(TestSessionItemTags, registerTag)
{
    const std::string name("tag");
    SessionItemTags tag;

    tag.registerTag(TagInfo::universalTag("abc"));
    EXPECT_TRUE(tag.exists("abc"));
    EXPECT_EQ(tag.defaultTag(), "");

    // registering default tag
    tag.registerTag(TagInfo::universalTag("abc2"), /*set_as_default*/true);
    EXPECT_TRUE(tag.exists("abc2"));
    EXPECT_EQ(tag.defaultTag(), "abc2");

    // registering tag with same name is not allowed
    EXPECT_THROW(tag.registerTag(TagInfo::universalTag("abc")), std::runtime_error);
}

//! Insert item.

TEST_F(TestSessionItemTags, insertItem)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";
    SessionItemTags tag;

    tag.registerTag(TagInfo::universalTag(tag1));
    tag.registerTag(TagInfo::universalTag(tag2));

    auto child_t1_a = new SessionItem;
    auto child_t1_b = new SessionItem;
    auto child_t2_a = new SessionItem;
    auto child_t2_b = new SessionItem;
    auto child_t2_c = new SessionItem;
    tag.insertItem(child_t2_a, -1, tag2);
    tag.insertItem(child_t2_c, -1, tag2);
    tag.insertItem(child_t1_a, -1, tag1);
    tag.insertItem(child_t1_b, -1, tag1);
    tag.insertItem(child_t2_b, 1, tag2); // between child_t2_a and child_t2_c

    std::vector<SessionItem*> expected = {child_t1_a, child_t1_b};
    EXPECT_EQ(tag.items(tag1), expected);
    expected = {child_t2_a, child_t2_b, child_t2_c};
    EXPECT_EQ(tag.items(tag2), expected);
}

