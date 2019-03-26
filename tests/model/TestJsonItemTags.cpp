#include "google_test.h"
#include "jsonitemtags.h"
#include "test_utils.h"
#include "jsonvariant.h"
#include "taginfo.h"
#include "obsoletesessionitemtags.h"
#include "customvariants.h"
#include <QJsonObject>
#include <QJsonArray>
#include <string>

using namespace ModelView;

//! Test convertion of SessionItemData from/to QJsonObject.

class TestJsonItemTags : public ::testing::Test
{
public:
    ~TestJsonItemTags();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }
};

const QString TestJsonItemTags::test_dir = "test_JsonItemTags";

TestJsonItemTags::~TestJsonItemTags() = default;

//! Checks if json object is correctly identified as representing TagInfo.

TEST_F(TestJsonItemTags, isItemTag)
{
    JsonItemTags converter;

    // valid json object representing DataRole
    QJsonObject object;
    object[JsonItemTags::nameKey] = QString::fromStdString("tag1");
    object[JsonItemTags::minKey] = 0;
    object[JsonItemTags::maxKey] = 1;
    object[JsonItemTags::countKey] = 10;
    object[JsonItemTags::modelsKey] = QJsonArray();

    EXPECT_TRUE(converter.is_item_tag(object));

    // invalid (not fuilly constructed) json object which can't represent DataRole
    QJsonObject object2;
    object2[JsonItemTags::minKey] = 42;
    EXPECT_FALSE(converter.is_item_tag(object2));
}

//! Creating QJsonArray from SessionItemData.

TEST_F(TestJsonItemTags, getJson)
{
    JsonItemTags converter;

    TagInfo tag1("tag1", 0, -1, std::vector<std::string>() = {});
    TagInfo tag2("tag2", 0, -1, std::vector<std::string>() = {"aaa", "bbb"});

    ObsoleteSessionItemTags tags;
    tags.registerTag(tag1);
    tags.registerTag(tag2);

    QJsonArray array = converter.get_json(tags);
    // it should contain two json objects
    EXPECT_EQ(array.size(), 2);
    EXPECT_TRUE(array[0].isObject());
    EXPECT_TRUE(array[1].isObject());

    // and these objects repesent DataRole
    EXPECT_TRUE(converter.is_item_tag(array[0].toObject()));
    EXPECT_TRUE(converter.is_item_tag(array[1].toObject()));
}

//! From SessionItemTags to json and back.

TEST_F(TestJsonItemTags, fromItemToJsonAndBack)
{
    JsonItemTags converter;

    TagInfo tag1("tag1", 0, -1, std::vector<std::string>() = {});
    TagInfo tag2("tag2", 0, 42, std::vector<std::string>() = {"aaa", "bbb"});

    ObsoleteSessionItemTags tags;
    tags.registerTag(tag1);
    tags.registerTag(tag2);

    QJsonArray array = converter.get_json(tags);
    // it should contain two json objects
    EXPECT_EQ(array.size(), 2);
    EXPECT_TRUE(array[0].isObject());
    EXPECT_TRUE(array[1].isObject());

    // and these objects repesent DataRole
    EXPECT_TRUE(converter.is_item_tag(array[0].toObject()));
    EXPECT_TRUE(converter.is_item_tag(array[1].toObject()));

    auto fileName = TestUtils::TestFileName(test_dir, "itemtags.json");
    TestUtils::SaveJson(array, fileName);

    // constructing from array
    auto tags2 = converter.get_tags(array);
    std::vector<TagInfo> result;
    for(const auto& x : tags2) {
        result.push_back(x);
    }

    EXPECT_EQ(result.size(), 2);

    // first reconstructed tag
    EXPECT_EQ(result[0].name(), "tag1");
    EXPECT_EQ(result[0].min(), 0);
    EXPECT_EQ(result[0].max(), -1);
    EXPECT_EQ(result[0].modelTypes(), std::vector<std::string>() = {});

    // second reconstructed tag
    EXPECT_EQ(result[1].name(), "tag2");
    EXPECT_EQ(result[1].min(), 0);
    EXPECT_EQ(result[1].max(), 42);
    std::vector<std::string> expected ={"aaa", "bbb"};
    EXPECT_EQ(result[1].modelTypes(), expected);
}


