#include "google_test.h"
#include "obsoletesessionitemtags.h"

using namespace ModelView;

class TestSessionItemTags : public ::testing::Test
{
public:
    ~TestSessionItemTags();

    const std::string ParticleType = "Particle";
    const std::string LayerType = "Layer";
};

TestSessionItemTags::~TestSessionItemTags() = default;

TEST_F(TestSessionItemTags, initialState)
{
    ObsoleteSessionItemTags tags;
    EXPECT_FALSE(tags.isValid(""));
    EXPECT_FALSE(tags.isValid("abc"));
}

TEST_F(TestSessionItemTags, registerTag)
{
    ObsoleteSessionItemTags tags;

    // registering tag
    std::vector<std::string> expected = {ParticleType};
    EXPECT_FALSE(tags.registerTag("", 0, 1, expected));

    EXPECT_TRUE(tags.registerTag("tag1", 0, 1, expected));
    EXPECT_TRUE(tags.isValid("tag1"));
    EXPECT_TRUE(tags.isValid("tag1", ParticleType));
    EXPECT_FALSE(tags.isValid("tag1", "wrongModelType"));
    EXPECT_EQ(tags.modelTypesForTag("tag1"), expected);

    // registering tag twice
    EXPECT_FALSE(tags.registerTag("tag1", 0, 1, expected));

    // registering another tag
    expected = {ParticleType, LayerType};
    EXPECT_TRUE(tags.registerTag("tag2", 0, 1, {ParticleType, LayerType}));
    EXPECT_EQ(tags.modelTypesForTag("tag2"), expected);
}

//! Registering tag from TagInfo object.

TEST_F(TestSessionItemTags, registerTagInfo)
{
    ObsoleteSessionItemTags tags;

    TagInfo tag = TagInfo::universalTag("tagname");
    tags.registerTag(tag);
    EXPECT_TRUE(tags.isValid(tag.name()));
}

TEST_F(TestSessionItemTags, modelTypesForTag)
{
    ObsoleteSessionItemTags tags;
    std::vector<std::string> expected{ParticleType, LayerType};

    EXPECT_TRUE(tags.registerTag("tag1", 0, 1, expected));
    EXPECT_EQ(tags.modelTypesForTag("tag1"), expected);

    EXPECT_TRUE(tags.registerTag("tag2", 0, 1, {}));
    EXPECT_EQ(tags.modelTypesForTag("tag2"), std::vector<std::string>());
    EXPECT_EQ(tags.modelTypesForTag("tag3"), std::vector<std::string>());
}

TEST_F(TestSessionItemTags, tagStartIndex)
{
    ObsoleteSessionItemTags tags;

    // registering tags
    EXPECT_TRUE(tags.registerTag("tag1", 0, 2, {ParticleType}));
    EXPECT_EQ(tags.childCount("tag1"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag1"), 0);

    EXPECT_TRUE(tags.registerTag("tag2", 0, 1, {ParticleType, LayerType}));
    EXPECT_EQ(tags.childCount("tag2"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag2"), 0);

    // adding child
    tags.addChild("tag1");
    tags.addChild("tag1");
    EXPECT_EQ(tags.childCount("tag1"), 2);
    EXPECT_EQ(tags.childCount("tag2"), 0);
    // attempt to add too much
    EXPECT_THROW(tags.addChild("tag1"), std::runtime_error);

    // checking start index
    EXPECT_EQ(tags.tagStartIndex("tag1"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag2"), 2);

    // removing child
    tags.removeChild("tag1");
    EXPECT_EQ(tags.tagStartIndex("tag1"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag2"), 1);

    // removing too much child
    tags.removeChild("tag1");
    EXPECT_THROW(tags.removeChild("tag1"), std::runtime_error);
    EXPECT_EQ(tags.tagStartIndex("tag1"), 0);
    EXPECT_EQ(tags.tagStartIndex("tag2"), 0);
}

TEST_F(TestSessionItemTags, indexFromTagRow)
{
    ObsoleteSessionItemTags tags;
    tags.registerTag("tag1", 0, -1, {ParticleType});
    tags.registerTag("tag2", 0, 2, {ParticleType});

    tags.addChild("tag1"); // index=0, row=0
    tags.addChild("tag1"); // index=1, row=1
    tags.addChild("tag1"); // index=2, row=2
    tags.addChild("tag2"); // index=3, row=0
    tags.addChild("tag2"); // index=4, row=1

    EXPECT_EQ(tags.indexFromTagRow("tag1", 0), 0);
    EXPECT_EQ(tags.indexFromTagRow("tag1", 1), 1);
    EXPECT_EQ(tags.indexFromTagRow("tag1", 2), 2);
    EXPECT_THROW(tags.indexFromTagRow("tag1", 3), std::runtime_error);
    EXPECT_THROW(tags.indexFromTagRow("tag1", -1), std::runtime_error);

    EXPECT_EQ(tags.indexFromTagRow("tag2", 0), 3);
    EXPECT_EQ(tags.indexFromTagRow("tag2", 1), 4);
}

TEST_F(TestSessionItemTags, tagFromIndex)
{
    ObsoleteSessionItemTags tags;
    tags.registerTag("tag1", 0, -1, {ParticleType});
    tags.registerTag("tag2", 0, 2, {ParticleType});

    tags.addChild("tag1"); // index=0
    tags.addChild("tag1"); // index=1
    tags.addChild("tag1"); // index=2
    tags.addChild("tag2"); // index=3
    tags.addChild("tag2"); // index=4

    EXPECT_EQ(tags.tagFromIndex(0), "tag1");
    EXPECT_EQ(tags.tagFromIndex(1), "tag1");
    EXPECT_EQ(tags.tagFromIndex(2), "tag1");
    EXPECT_EQ(tags.tagFromIndex(3), "tag2");
    EXPECT_EQ(tags.tagFromIndex(4), "tag2");

    EXPECT_EQ(tags.tagFromIndex(-1), "");
    EXPECT_EQ(tags.tagFromIndex(5), "");
}

//! Testing the method calculating insert index.

TEST_F(TestSessionItemTags, insertIndexFromTagRow)
{
    ObsoleteSessionItemTags tags;
    tags.registerTag("tag1", 0, -1, {ParticleType});
    tags.registerTag("tag2", 0, 2, {ParticleType});

    tags.addChild("tag1"); // index=0, row=0
    tags.addChild("tag1"); // index=1, row=1
    tags.addChild("tag1"); // index=2, row=2
    tags.addChild("tag2"); // index=3, row=0

    EXPECT_EQ(tags.insertIndexFromTagRow("tag1", 0), 0);
    EXPECT_EQ(tags.insertIndexFromTagRow("tag1", -1), 3);
    EXPECT_EQ(tags.insertIndexFromTagRow("tag1", 3), 3);
    EXPECT_THROW(tags.insertIndexFromTagRow("tag1", 4), std::runtime_error); // too big

    EXPECT_EQ(tags.insertIndexFromTagRow("tag2", 0), 3);
    EXPECT_EQ(tags.insertIndexFromTagRow("tag2", -1), 4);
    tags.addChild("tag2");                                 // index=4, row=1
    EXPECT_EQ(tags.insertIndexFromTagRow("tag2", 0), -1);  // maximum reached
    EXPECT_EQ(tags.insertIndexFromTagRow("tag2", -1), -1); // maximum reached
}

//! Tag summary info

TEST_F(TestSessionItemTags, tagSummaryInfo)
{
    ObsoleteSessionItemTags tags;
    tags.registerTag("tag1", 0, -1, {ParticleType});
    tags.registerTag("tag2", 0, 2, {ParticleType});

    tags.addChild("tag1"); // index=0, row=0
    tags.addChild("tag1"); // index=1, row=1
    tags.addChild("tag1"); // index=2, row=2
    tags.addChild("tag2"); // index=3, row=0

    std::vector<std::pair<int, std::string>> expected
        = {{0, "tag1"}, {1, "tag1"}, {2, "tag1"}, {0, "tag2"}};
    EXPECT_EQ(tags.tagsSummary(), expected);
}
