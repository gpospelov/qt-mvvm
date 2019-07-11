#include "google_test.h"
#include "sessionitem.h"
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
    EXPECT_EQ(tag.defaultTag(), "");

    EXPECT_FALSE(tag.isTag("abc"));
}

//! Registering tags.

TEST_F(TestSessionItemTags, registerTag)
{
    const std::string name("tag");
    SessionItemTags tag;

    tag.registerTag(TagInfo::universalTag("abc"));
    EXPECT_TRUE(tag.isTag("abc"));
    EXPECT_EQ(tag.defaultTag(), "");

    // registering default tag
    tag.registerTag(TagInfo::universalTag("abc2"), /*set_as_default*/ true);
    EXPECT_TRUE(tag.isTag("abc2"));
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

    // inserting items without tags defined
    auto item = std::make_unique<SessionItem>();
    EXPECT_THROW(tag.insertItem(item.get(), "", -1), std::runtime_error);

    // registering tags
    tag.registerTag(TagInfo::universalTag(tag1));
    tag.registerTag(TagInfo::universalTag(tag2));

    // inserting items
    auto child_t1_a = new SessionItem;
    auto child_t1_b = new SessionItem;
    auto child_t2_a = new SessionItem;
    auto child_t2_b = new SessionItem;
    auto child_t2_c = new SessionItem;
    EXPECT_TRUE(tag.insertItem(child_t2_a, tag2, -1));
    EXPECT_TRUE(tag.insertItem(child_t2_c, tag2, -1));
    EXPECT_TRUE(tag.insertItem(child_t1_a, tag1, -1));
    EXPECT_TRUE(tag.insertItem(child_t1_b, tag1, -1));
    EXPECT_TRUE(tag.insertItem(child_t2_b, tag2, 1)); // between child_t2_a and child_t2_c

    // checking item order in containers
    std::vector<SessionItem*> expected = {child_t1_a, child_t1_b};
    EXPECT_EQ(tag.getItems(tag1), expected);
    expected = {child_t2_a, child_t2_b, child_t2_c};
    EXPECT_EQ(tag.getItems(tag2), expected);

    // checking allitems order
    expected = {child_t1_a, child_t1_b, child_t2_a, child_t2_b, child_t2_c};
    EXPECT_EQ(tag.allitems(), expected);
}

//! Testing method tagRowOfItem.

TEST_F(TestSessionItemTags, tagRowOfItem)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    SessionItemTags tag;
    tag.registerTag(TagInfo::universalTag(tag1), /*set_as_default*/ true);
    tag.registerTag(TagInfo::universalTag(tag2));

    // inserting children
    auto child_t1_a = new SessionItem;
    auto child_t1_b = new SessionItem;
    auto child_t2_a = new SessionItem;
    tag.insertItem(child_t1_a, "", -1);      // 0
    tag.insertItem(child_t1_b, "", -1);      // 1
    tag.insertItem(child_t2_a, tag2, 0); // 0

    // checking children tag and row
    EXPECT_EQ(tag.tagRowOfItem(child_t1_a).first, tag1);
    EXPECT_EQ(tag.tagRowOfItem(child_t1_b).first, tag1);
    EXPECT_EQ(tag.tagRowOfItem(child_t2_a).first, tag2);
    EXPECT_EQ(tag.tagRowOfItem(child_t1_a).second, 0);
    EXPECT_EQ(tag.tagRowOfItem(child_t1_b).second, 1);
    EXPECT_EQ(tag.tagRowOfItem(child_t2_a).second, 0);

    // alien item has no tag and -1 row
    auto alien = std::make_unique<SessionItem>();
    EXPECT_EQ(tag.tagRowOfItem(alien.get()).first, "");
    EXPECT_EQ(tag.tagRowOfItem(alien.get()).second, -1);

    // the same for nullptr
    EXPECT_EQ(tag.tagRowOfItem(nullptr).first, "");
    EXPECT_EQ(tag.tagRowOfItem(nullptr).second, -1);
}

//! Testing method getItem.

TEST_F(TestSessionItemTags, getItem)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";

    // creating parent with one tag
    SessionItemTags tag;
    tag.registerTag(TagInfo::universalTag(tag1), /*set_as_default*/ true);
    tag.registerTag(TagInfo::universalTag(tag2));

    // inserting children
    auto child_t1_a = new SessionItem;
    auto child_t1_b = new SessionItem;
    auto child_t2_a = new SessionItem;
    tag.insertItem(child_t1_a, "", -1);      // 0
    tag.insertItem(child_t1_b, "", -1);      // 1
    tag.insertItem(child_t2_a, tag2, 0); // 0

    EXPECT_EQ(tag.getItem(tag1), child_t1_a);
    EXPECT_EQ(tag.getItem(tag1, 0), child_t1_a);
    EXPECT_EQ(tag.getItem(tag1, 1), child_t1_b);
    EXPECT_EQ(tag.getItem(tag2, 0), child_t2_a);
    EXPECT_EQ(tag.getItem(tag2, 2), nullptr);
}

//! Testing method getItem.

TEST_F(TestSessionItemTags, takeItem)
{
    const std::string tag1 = "tag1";
    const std::string tag2 = "tag2";
    const std::string model_type("model");

    SessionItemTags tag;
    tag.registerTag(TagInfo::universalTag(tag1), /*set_as_default*/ true);
    tag.registerTag(TagInfo::universalTag(tag2));

    // taking non existing items
    EXPECT_EQ(tag.takeItem("", 0), nullptr);

    // inserting items
    auto child1 = new SessionItem(model_type);
    auto child2 = new SessionItem(model_type);
    auto child3 = new SessionItem(model_type);
    auto child4 = new SessionItem(model_type);
    EXPECT_TRUE(tag.insertItem(child1, "", -1));
    EXPECT_TRUE(tag.insertItem(child2, "", -1));
    EXPECT_TRUE(tag.insertItem(child3, "", -1));
    EXPECT_TRUE(tag.insertItem(child4, tag2, -1));

    // taking item in between
    auto taken2 = tag.takeItem("", 1);
    EXPECT_EQ(child2, taken2);
    delete taken2;

    // order of remaining children
    std::vector<SessionItem*> expected = {child1, child3};
    EXPECT_EQ(tag.getItems(tag1), expected);
    expected = {child4};
    EXPECT_EQ(tag.getItems(tag2), expected);

    // taking non existing items
    EXPECT_EQ(tag.takeItem("", -1), nullptr);
}

//! Testing isSinglePropertyTag.

TEST_F(TestSessionItemTags, isSinglePropertyTag)
{
    SessionItemTags tag;
    tag.registerTag(TagInfo::universalTag("universal"), /*set_as_default*/ true);
    EXPECT_FALSE(tag.isSinglePropertyTag("universal"));

    tag.registerTag(TagInfo::propertyTag("property_tag", "Vector"));
    EXPECT_TRUE(tag.isSinglePropertyTag("property_tag"));

    EXPECT_FALSE(tag.isSinglePropertyTag("unexisting tag"));
}

